#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BLOCK_BYTES ; 
 int DICTIONARY_BYTES ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char*) ; 
 int compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_bin (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  seek_bin (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  test_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  test_decompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int,int) ; 

int main(int argc, char* argv[])
{
    char inpFilename[256] = { 0 };
    char lz4Filename[256] = { 0 };
    char decFilename[256] = { 0 };
    char dictFilename[256] = { 0 };
    int offset;
    int length;
    char dict[DICTIONARY_BYTES];
    int dictSize;

    if(argc < 5) {
        printf("Usage: %s input dictionary offset length", argv[0]);
        return 0;
    }

    snprintf(inpFilename, 256, "%s", argv[1]);
    snprintf(lz4Filename, 256, "%s.lz4s-%d", argv[1], BLOCK_BYTES);
    snprintf(decFilename, 256, "%s.lz4s-%d.dec", argv[1], BLOCK_BYTES);
    snprintf(dictFilename, 256, "%s", argv[2]);
    offset = atoi(argv[3]);
    length = atoi(argv[4]);

    printf("inp    = [%s]\n", inpFilename);
    printf("lz4    = [%s]\n", lz4Filename);
    printf("dec    = [%s]\n", decFilename);
    printf("dict   = [%s]\n", dictFilename);
    printf("offset = [%d]\n", offset);
    printf("length = [%d]\n", length);

    /* Load dictionary */
    {
        FILE* dictFp = fopen(dictFilename, "rb");
        dictSize = (int)read_bin(dictFp, dict, DICTIONARY_BYTES);
        fclose(dictFp);
    }

    /* compress */
    {
        FILE* inpFp = fopen(inpFilename, "rb");
        FILE* outFp = fopen(lz4Filename, "wb");

        printf("compress : %s -> %s\n", inpFilename, lz4Filename);
        test_compress(outFp, inpFp, dict, dictSize);
        printf("compress : done\n");

        fclose(outFp);
        fclose(inpFp);
    }

    /* decompress */
    {
        FILE* inpFp = fopen(lz4Filename, "rb");
        FILE* outFp = fopen(decFilename, "wb");

        printf("decompress : %s -> %s\n", lz4Filename, decFilename);
        test_decompress(outFp, inpFp, dict, DICTIONARY_BYTES, offset, length);
        printf("decompress : done\n");

        fclose(outFp);
        fclose(inpFp);
    }

    /* verify */
    {
        FILE* inpFp = fopen(inpFilename, "rb");
        FILE* decFp = fopen(decFilename, "rb");
        seek_bin(inpFp, offset, SEEK_SET);

        printf("verify : %s <-> %s\n", inpFilename, decFilename);
        const int cmp = compare(inpFp, decFp, length);
        if(0 == cmp) {
            printf("verify : OK\n");
        } else {
            printf("verify : NG\n");
        }

        fclose(decFp);
        fclose(inpFp);
    }

    return 0;
}