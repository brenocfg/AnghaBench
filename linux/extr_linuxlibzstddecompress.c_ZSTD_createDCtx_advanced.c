#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  customMem ;
struct TYPE_8__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
struct TYPE_9__ {int /*<<< orphan*/  customMem; } ;
typedef  TYPE_2__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_decompressBegin (TYPE_2__*) ; 
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

ZSTD_DCtx *ZSTD_createDCtx_advanced(ZSTD_customMem customMem)
{
	ZSTD_DCtx *dctx;

	if (!customMem.customAlloc || !customMem.customFree)
		return NULL;

	dctx = (ZSTD_DCtx *)ZSTD_malloc(sizeof(ZSTD_DCtx), customMem);
	if (!dctx)
		return NULL;
	memcpy(&dctx->customMem, &customMem, sizeof(customMem));
	ZSTD_decompressBegin(dctx);
	return dctx;
}