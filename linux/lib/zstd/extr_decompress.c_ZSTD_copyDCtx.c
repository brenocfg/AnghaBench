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
 size_t WILDCOPY_OVERLENGTH ; 
 size_t ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 
 size_t ZSTD_frameHeaderSize_max ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void ZSTD_copyDCtx(ZSTD_DCtx *dstDCtx, const ZSTD_DCtx *srcDCtx)
{
	size_t const workSpaceSize = (ZSTD_BLOCKSIZE_ABSOLUTEMAX + WILDCOPY_OVERLENGTH) + ZSTD_frameHeaderSize_max;
	memcpy(dstDCtx, srcDCtx, sizeof(ZSTD_DCtx) - workSpaceSize); /* no need to copy workspace */
}