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
typedef  int /*<<< orphan*/  LZ4F_frameInfo_t ;
typedef  int /*<<< orphan*/  LZ4F_dctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LZ4F_HEADER_SIZE_MAX ; 
 char* LZ4F_getErrorName (size_t const) ; 
 size_t LZ4F_getFrameInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t*) ; 
 scalar_t__ LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int decompress_file_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,size_t const,size_t,void* const,size_t const) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void* const) ; 
 size_t get_block_size (int /*<<< orphan*/ *) ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
decompress_file_allocDst(FILE* f_in, FILE* f_out,
                        LZ4F_dctx* dctx,
                        void* src, size_t srcCapacity)
{
    assert(f_in != NULL); assert(f_out != NULL);
    assert(dctx != NULL);
    assert(src != NULL);
    assert(srcCapacity >= LZ4F_HEADER_SIZE_MAX);  /* ensure LZ4F_getFrameInfo() can read enough data */

    /* Read Frame header */
    size_t const readSize = fread(src, 1, srcCapacity, f_in);
    if (readSize == 0 || ferror(f_in)) {
        printf("Decompress: not enough input or error reading file\n");
        return 1;
    }

    LZ4F_frameInfo_t info;
    size_t consumedSize = readSize;
    {   size_t const fires = LZ4F_getFrameInfo(dctx, &info, src, &consumedSize);
        if (LZ4F_isError(fires)) {
            printf("LZ4F_getFrameInfo error: %s\n", LZ4F_getErrorName(fires));
            return 1;
    }   }

    /* Allocating enough space for an entire block isn't necessary for
     * correctness, but it allows some memcpy's to be elided.
     */
    size_t const dstCapacity = get_block_size(&info);
    void* const dst = malloc(dstCapacity);
    if (!dst) { perror("decompress_file(dst)"); return 1; }

    int const decompressionResult = decompress_file_internal(
                        f_in, f_out,
                        dctx,
                        src, srcCapacity, readSize-consumedSize, consumedSize,
                        dst, dstCapacity);

    free(dst);
    return decompressionResult;
}