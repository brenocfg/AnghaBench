#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opts ;
struct TYPE_4__ {int stableDst; } ;
typedef  TYPE_1__ LZ4F_decompressOptions_t ;
typedef  int /*<<< orphan*/  LZ4F_dctx ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int /*<<< orphan*/  LZ4F_VERSION ; 
 int /*<<< orphan*/  LZ4F_createDecompressionContext (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 size_t LZ4F_decompress (int /*<<< orphan*/ *,void*,size_t*,void const*,size_t*,TYPE_1__*) ; 
 int /*<<< orphan*/  LZ4F_freeDecompressionContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

size_t FUZZ_decompressFrame(void* dst, const size_t dstCapacity,
                            const void* src, const size_t srcSize)
{
    LZ4F_decompressOptions_t opts;
    memset(&opts, 0, sizeof(opts));
    opts.stableDst = 1;
    LZ4F_dctx* dctx;
    LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION);
    FUZZ_ASSERT(dctx);

    size_t dstSize = dstCapacity;
    size_t srcConsumed = srcSize;
    size_t const rc =
            LZ4F_decompress(dctx, dst, &dstSize, src, &srcConsumed, &opts);
    FUZZ_ASSERT(!LZ4F_isError(rc));
    FUZZ_ASSERT(rc == 0);
    FUZZ_ASSERT(srcConsumed == srcSize);

    LZ4F_freeDecompressionContext(dctx);

    return dstSize;
}