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
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t HUF_decompress1X2_DCtx_wksp (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,void*,size_t) ; 
 size_t HUF_decompress1X4_DCtx_wksp (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,void*,size_t) ; 
 scalar_t__ HUF_selectDecoder (size_t,size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/  const,size_t) ; 

size_t HUF_decompress1X_DCtx_wksp(HUF_DTable *dctx, void *dst, size_t dstSize, const void *cSrc, size_t cSrcSize, void *workspace, size_t workspaceSize)
{
	/* validation checks */
	if (dstSize == 0)
		return ERROR(dstSize_tooSmall);
	if (cSrcSize > dstSize)
		return ERROR(corruption_detected); /* invalid */
	if (cSrcSize == dstSize) {
		memcpy(dst, cSrc, dstSize);
		return dstSize;
	} /* not compressed */
	if (cSrcSize == 1) {
		memset(dst, *(const BYTE *)cSrc, dstSize);
		return dstSize;
	} /* RLE */

	{
		U32 const algoNb = HUF_selectDecoder(dstSize, cSrcSize);
		return algoNb ? HUF_decompress1X4_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize)
			      : HUF_decompress1X2_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize);
	}
}