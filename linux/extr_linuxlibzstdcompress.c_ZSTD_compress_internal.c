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
typedef  int /*<<< orphan*/  ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compressBegin_internal (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,size_t) ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

__attribute__((used)) static size_t ZSTD_compress_internal(ZSTD_CCtx *cctx, void *dst, size_t dstCapacity, const void *src, size_t srcSize, const void *dict, size_t dictSize,
				     ZSTD_parameters params)
{
	CHECK_F(ZSTD_compressBegin_internal(cctx, dict, dictSize, params, srcSize));
	return ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
}