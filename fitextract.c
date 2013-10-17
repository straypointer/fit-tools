#include <stdio.h>

FILE* _file;
void process(FILE* handle);


int main(int argc, char** argv) {

	if (argc < 2) {
		printf("USAGE: fitextract <file>\n");
		return 0;
	}

	printf("processing %s\n", argv[1]);
	_file = fopen(argv[1], "r");

	if (_file != NULL) {
		process(_file);
		fclose(_file);
	}
}

void process(FILE* handle) {
	char buf[512];
	size_t bytesread = 0;
	int processing = 0;
	int filesoutput = 0;
	FILE* target = NULL;
	char targetname[512];
	int byteswritten = 0;
	int blockswritten = 0;

	while (bytesread = fread(buf, 512, 1, handle)) {
		unsigned int* p = (unsigned int *) buf;
		if (*p == 0x0098100E) {
			printf("Found header\n");
			sprintf(targetname, "./output/file%03d.fit", filesoutput++);
			target = fopen(targetname, "w");
			do {
				blockswritten += fwrite(buf, 512, 1, target);
				byteswritten = blockswritten * 512;
				bytesread = fread(buf, 512, 1, handle);
//				printf("0x%0x\n", *p);
				if (blockswritten > 1000) break;
			} while (bytesread && (*p != 0x0098100E) && (*p != 0xFFFFFFFF));

			if (bytesread) fseek(handle, -512, SEEK_CUR);
			fclose(target);
			byteswritten = 0;
			blockswritten = 0;
		}
//		printf("0x%x\n", *p);		
	}
}

void dumpfit(FILE* handle, FILE* target) {

}

