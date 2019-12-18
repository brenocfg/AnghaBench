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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressContinue_internal (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ZSTD_getBlockSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_compressBlock(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
    size_t const blockSizeMax = ZSTD_getBlockSize(cctx);
    if (srcSize > blockSizeMax) return ERROR(srcSize_wrong);

    return ZSTD_compressContinue_internal(cctx, dst, dstCapacity, src, srcSize, 0 /* frame mode */, 0 /* last chunk */);
}