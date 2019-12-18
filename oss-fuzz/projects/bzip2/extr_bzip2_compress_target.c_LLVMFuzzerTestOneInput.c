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
 int BZ2_bzBuffToBuffCompress (char*,unsigned int*,char*,size_t,int,int /*<<< orphan*/ ,int) ; 
 int BZ2_bzBuffToBuffDecompress (char*,unsigned int*,char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    int r, blockSize100k, workFactor, small;
    unsigned int nZ, nOut;

    /* Copying @julian-seward1's comment from
     * https://github.com/google/oss-fuzz/pull/1887#discussion_r226852388
     *
     * They just reflect the fact that the worst case output size is 101%
     * of the input size + 600 bytes (I assume -- this is now nearly 20
     * years old). Since the buffer is in mallocville, presumably asan
     * will complain if it gets overrun. I doubt that will happen though.
     */
    nZ = size + 600 + (size / 100);
    char *zbuf = malloc(nZ);

    blockSize100k = (size % 11) + 1;
    if (blockSize100k > 9) {
        blockSize100k = 9;
    }
    workFactor = size % 251;

    // Choose highest compression (blockSize100k=9)
    r = BZ2_bzBuffToBuffCompress(zbuf, &nZ, (char *)data, size,
            blockSize100k, /*verbosity=*/0, workFactor);
    if (r != BZ_OK) {
#ifdef __DEBUG__
        fprintf(stdout, "Compression error: %d\n", r);
#endif
        free(zbuf);
        return 0;
    }

    nOut = size*2;
    char *outbuf = malloc(nOut);
    small = size % 2;
    r = BZ2_bzBuffToBuffDecompress(outbuf, &nOut, zbuf, nZ, small,
            /*verbosity=*/0);
    if (r != BZ_OK) {
#ifdef __DEBUG__
        fprintf(stdout, "Decompression error: %d\n", r);
#endif
        free(zbuf);
        free(outbuf);
        return 0;
    }

    assert(nOut == size);
    assert(memcmp(data, outbuf, size) == 0);
    free(zbuf);
    free(outbuf);
    return 0;
}