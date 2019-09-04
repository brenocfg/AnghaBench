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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createDCtx_advanced (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_initStack (void*,size_t) ; 

ZSTD_DCtx *ZSTD_initDCtx(void *workspace, size_t workspaceSize)
{
	ZSTD_customMem const stackMem = ZSTD_initStack(workspace, workspaceSize);
	return ZSTD_createDCtx_advanced(stackMem);
}