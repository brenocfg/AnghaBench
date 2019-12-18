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
typedef  int /*<<< orphan*/  LZ4F_dctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LZ4F_decompress (int /*<<< orphan*/ *,void*,size_t*,void const*,size_t*,int /*<<< orphan*/ *) ; 
 char* LZ4F_getErrorName (size_t) ; 
 scalar_t__ LZ4F_isError (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  safe_fwrite (void*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
decompress_file_internal(FILE* f_in, FILE* f_out,
                         LZ4F_dctx* dctx,
                         void* src, size_t srcCapacity, size_t filled, size_t alreadyConsumed,
                         void* dst, size_t dstCapacity)
{
    int firstChunk = 1;
    size_t ret = 1;

    assert(f_in != NULL); assert(f_out != NULL);
    assert(dctx != NULL);
    assert(src != NULL); assert(srcCapacity > 0); assert(filled <= srcCapacity); assert(alreadyConsumed <= filled);
    assert(dst != NULL); assert(dstCapacity > 0);

    /* Decompression */
    while (ret != 0) {
        /* Load more input */
        size_t readSize = firstChunk ? filled : fread(src, 1, srcCapacity, f_in); firstChunk=0;
        const void* srcPtr = (const char*)src + alreadyConsumed; alreadyConsumed=0;
        const void* const srcEnd = (const char*)srcPtr + readSize;
        if (readSize == 0 || ferror(f_in)) {
            printf("Decompress: not enough input or error reading file\n");
            return 1;
        }

        /* Decompress:
         * Continue while there is more input to read (srcPtr != srcEnd)
         * and the frame isn't over (ret != 0)
         */
        while (srcPtr < srcEnd && ret != 0) {
            /* Any data within dst has been flushed at this stage */
            size_t dstSize = dstCapacity;
            size_t srcSize = (const char*)srcEnd - (const char*)srcPtr;
            ret = LZ4F_decompress(dctx, dst, &dstSize, srcPtr, &srcSize, /* LZ4F_decompressOptions_t */ NULL);
            if (LZ4F_isError(ret)) {
                printf("Decompression error: %s\n", LZ4F_getErrorName(ret));
                return 1;
            }
            /* Flush output */
            if (dstSize != 0) safe_fwrite(dst, 1, dstSize, f_out);
            /* Update input */
            srcPtr = (const char*)srcPtr + srcSize;
        }

        assert(srcPtr <= srcEnd);

        /* Ensure all input data has been consumed.
         * It is valid to have multiple frames in the same file,
         * but this example only supports one frame.
         */
        if (srcPtr < srcEnd) {
            printf("Decompress: Trailing data left in file after frame\n");
            return 1;
        }
    }

    /* Check that there isn't trailing data in the file after the frame.
     * It is valid to have multiple frames in the same file,
     * but this example only supports one frame.
     */
    {   size_t const readSize = fread(src, 1, 1, f_in);
        if (readSize != 0 || !feof(f_in)) {
            printf("Decompress: Trailing data left in file after frame\n");
            return 1;
    }   }

    return 0;
}