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
 int compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  test_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  test_decompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int main(int argc, char* argv[])
{
    enum {
        MESSAGE_MAX_BYTES   = 1024,
        RING_BUFFER_BYTES   = 1024 * 256 + MESSAGE_MAX_BYTES,
    };

    char inpFilename[256] = { 0 };
    char lz4Filename[256] = { 0 };
    char decFilename[256] = { 0 };

    if (argc < 2)
    {
        printf("Please specify input filename\n");
        return 0;
    }

    snprintf(inpFilename, 256, "%s", argv[1]);
    snprintf(lz4Filename, 256, "%s.lz4s", argv[1]);
    snprintf(decFilename, 256, "%s.lz4s.dec", argv[1]);

    printf("inp = [%s]\n", inpFilename);
    printf("lz4 = [%s]\n", lz4Filename);
    printf("dec = [%s]\n", decFilename);

    // compress
    {
        FILE* inpFp = fopen(inpFilename, "rb");
        FILE* outFp = fopen(lz4Filename, "wb");

        test_compress(outFp, inpFp, MESSAGE_MAX_BYTES, RING_BUFFER_BYTES);

        fclose(outFp);
        fclose(inpFp);
    }

    // decompress
    {
        FILE* inpFp = fopen(lz4Filename, "rb");
        FILE* outFp = fopen(decFilename, "wb");

        test_decompress(outFp, inpFp, MESSAGE_MAX_BYTES, RING_BUFFER_BYTES);

        fclose(outFp);
        fclose(inpFp);
    }

    // verify
    {
        FILE* inpFp = fopen(inpFilename, "rb");
        FILE* decFp = fopen(decFilename, "rb");

        const int cmp = compare(inpFp, decFp);
        if (0 == cmp)
            printf("Verify : OK\n");
        else
            printf("Verify : NG\n");

        fclose(decFp);
        fclose(inpFp);
    }

    return 0;
}