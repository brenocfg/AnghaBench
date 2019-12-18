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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 size_t ZSTD_decompressMultiFrame (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,void const*,size_t,int /*<<< orphan*/ *) ; 

size_t ZSTD_decompress_usingDict(ZSTD_DCtx *dctx, void *dst, size_t dstCapacity, const void *src, size_t srcSize, const void *dict, size_t dictSize)
{
	return ZSTD_decompressMultiFrame(dctx, dst, dstCapacity, src, srcSize, dict, dictSize, NULL);
}