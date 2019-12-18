#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int error; double size_in; scalar_t__ size_out; } ;
typedef  TYPE_1__ compressResult_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int compareFiles (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 TYPE_1__ compress_file (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int decompress_file (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

int main(int argc, const char **argv) {
    char inpFilename[256] = { 0 };
    char lz4Filename[256] = { 0 };
    char decFilename[256] = { 0 };

    if (argc < 2) {
        printf("Please specify input filename\n");
        return 0;
    }

    snprintf(inpFilename, 256, "%s", argv[1]);
    snprintf(lz4Filename, 256, "%s.lz4", argv[1]);
    snprintf(decFilename, 256, "%s.lz4.dec", argv[1]);

    printf("inp = [%s]\n", inpFilename);
    printf("lz4 = [%s]\n", lz4Filename);
    printf("dec = [%s]\n", decFilename);

    /* compress */
    {   FILE* const inpFp = fopen(inpFilename, "rb");
        FILE* const outFp = fopen(lz4Filename, "wb");

        printf("compress : %s -> %s\n", inpFilename, lz4Filename);
        compressResult_t const ret = compress_file(inpFp, outFp);

        fclose(outFp);
        fclose(inpFp);

        if (ret.error) {
            printf("compress : failed with code %i\n", ret.error);
            return ret.error;
        }
        printf("%s: %zu → %zu bytes, %.1f%%\n",
            inpFilename,
            (size_t)ret.size_in, (size_t)ret.size_out,  /* might overflow is size_t is 32 bits and size_{in,out} > 4 GB */
            (double)ret.size_out / ret.size_in * 100);
        printf("compress : done\n");
    }

    /* decompress */
    {   FILE* const inpFp = fopen(lz4Filename, "rb");
        FILE* const outFp = fopen(decFilename, "wb");

        printf("decompress : %s -> %s\n", lz4Filename, decFilename);
        int const ret = decompress_file(inpFp, outFp);

        fclose(outFp);
        fclose(inpFp);

        if (ret) {
            printf("decompress : failed with code %i\n", ret);
            return ret;
        }
        printf("decompress : done\n");
    }

    /* verify */
    {   FILE* const inpFp = fopen(inpFilename, "rb");
        FILE* const decFp = fopen(decFilename, "rb");

        printf("verify : %s <-> %s\n", inpFilename, decFilename);
        int const cmp = compareFiles(inpFp, decFp);

        fclose(decFp);
        fclose(inpFp);

        if (cmp) {
            printf("corruption detected : decompressed file differs from original\n");
            return cmp;
        }
        printf("verify : OK\n");
    }

    return 0;
}