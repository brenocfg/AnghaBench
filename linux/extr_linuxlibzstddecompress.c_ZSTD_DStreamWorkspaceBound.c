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
typedef  int /*<<< orphan*/  ZSTD_DStream ;

/* Variables and functions */
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int WILDCOPY_OVERLENGTH ; 
 size_t ZSTD_ALIGN (size_t const) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 
 size_t ZSTD_DCtxWorkspaceBound () ; 

size_t ZSTD_DStreamWorkspaceBound(size_t maxWindowSize)
{
	size_t const blockSize = MIN(maxWindowSize, ZSTD_BLOCKSIZE_ABSOLUTEMAX);
	size_t const inBuffSize = blockSize;
	size_t const outBuffSize = maxWindowSize + blockSize + WILDCOPY_OVERLENGTH * 2;
	return ZSTD_DCtxWorkspaceBound() + ZSTD_ALIGN(sizeof(ZSTD_DStream)) + ZSTD_ALIGN(inBuffSize) + ZSTD_ALIGN(outBuffSize);
}