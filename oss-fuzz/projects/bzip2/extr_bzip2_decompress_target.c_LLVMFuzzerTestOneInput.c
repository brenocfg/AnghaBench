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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int BZ2_bzBuffToBuffDecompress (char*,unsigned int*,char*,size_t,int,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  stdout ; 

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    int r, small;
    unsigned int nZ, nOut;

    // See: https://github.com/google/bzip2-rpc/blob/master/unzcrash.c#L39
    nOut = size*2;
    char *outbuf = malloc(nOut);
    small = size % 2;
    r = BZ2_bzBuffToBuffDecompress(outbuf, &nOut, (char *)data, size,
            small, /*verbosity=*/0);

    if (r != BZ_OK) {
#ifdef __DEBUG__
        fprintf(stdout, "Decompression error: %d\n", r);
#endif
    }
    free(outbuf);
    return 0;
}