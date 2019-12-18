#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  customMem; struct TYPE_4__* workSpace; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

size_t ZSTD_freeCCtx(ZSTD_CCtx *cctx)
{
	if (cctx == NULL)
		return 0; /* support free on NULL */
	ZSTD_free(cctx->workSpace, cctx->customMem);
	ZSTD_free(cctx, cctx->customMem);
	return 0; /* reserved as a potential error code in the future */
}