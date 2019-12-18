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
 int compare (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  test_compress (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  test_decompress (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 

int main(int argc, char** argv)
{
    char inpFilename[256] = { 0 };
    char lz4Filename[256] = { 0 };
    char decFilename[256] = { 0 };

    if (argc < 2) {
        printf("Please specify input filename\n");
        return 0;
    }

    snprintf(inpFilename, 256, "%s", argv[1]);
    snprintf(lz4Filename, 256, "%s.lz4s-%d", argv[1], 0);
    snprintf(decFilename, 256, "%s.lz4s-%d.dec", argv[1], 0);

    printf("inp = [%s]\n", inpFilename);
    printf("lz4 = [%s]\n", lz4Filename);
    printf("dec = [%s]\n", decFilename);

    // compress
    {   FILE* const inpFp = fopen(inpFilename, "rb");
        FILE* const outFp = fopen(lz4Filename, "wb");

        test_compress(outFp, inpFp);

        fclose(outFp);
        fclose(inpFp);
    }

    // decompress
    {   FILE* const inpFp = fopen(lz4Filename, "rb");
        FILE* const outFp = fopen(decFilename, "wb");

        test_decompress(outFp, inpFp);

        fclose(outFp);
        fclose(inpFp);
    }

    // verify
    {   FILE* const inpFp = fopen(inpFilename, "rb");
        FILE* const decFp = fopen(decFilename, "rb");

        const int cmp = compare(inpFp, decFp);
        if (0 == cmp) {
            printf("Verify : OK\n");
        } else {
            printf("Verify : NG\n");
        }

        fclose(decFp);
        fclose(inpFp);
    }

    return 0;
}