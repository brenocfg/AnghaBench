#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_5__ {int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  workSpaceSize; TYPE_1__ customMem; int /*<<< orphan*/  workSpace; } ;
typedef  TYPE_2__ ZSTD_CCtx ;

/* Variables and functions */
 TYPE_2__* ZSTD_createCCtx_advanced (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_initStack (void*,size_t) ; 
 int /*<<< orphan*/  ZSTD_stackAllocAll (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ZSTD_CCtx *ZSTD_initCCtx(void *workspace, size_t workspaceSize)
{
	ZSTD_customMem const stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_CCtx *cctx = ZSTD_createCCtx_advanced(stackMem);
	if (cctx) {
		cctx->workSpace = ZSTD_stackAllocAll(cctx->customMem.opaque, &cctx->workSpaceSize);
	}
	return cctx;
}