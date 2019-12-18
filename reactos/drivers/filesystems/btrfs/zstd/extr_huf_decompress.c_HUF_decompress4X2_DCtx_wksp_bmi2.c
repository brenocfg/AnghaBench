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
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t HUF_decompress4X2_usingDTable_internal (void*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HUF_isError (size_t) ; 
 size_t HUF_readDTableX2_wksp (int /*<<< orphan*/ *,void const*,size_t,void*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t HUF_decompress4X2_DCtx_wksp_bmi2(HUF_DTable* dctx, void* dst, size_t dstSize,
                                   const void* cSrc, size_t cSrcSize,
                                   void* workSpace, size_t wkspSize, int bmi2)
{
    const BYTE* ip = (const BYTE*) cSrc;

    size_t hSize = HUF_readDTableX2_wksp(dctx, cSrc, cSrcSize,
                                         workSpace, wkspSize);
    if (HUF_isError(hSize)) return hSize;
    if (hSize >= cSrcSize) return ERROR(srcSize_wrong);
    ip += hSize; cSrcSize -= hSize;

    return HUF_decompress4X2_usingDTable_internal(dst, dstSize, ip, cSrcSize, dctx, bmi2);
}