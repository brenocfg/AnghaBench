#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_parameters ;
struct TYPE_4__ {scalar_t__ litLengthSum; } ;
struct TYPE_5__ {int /*<<< orphan*/  xxhState; TYPE_1__ seqStore; int /*<<< orphan*/ * rep; scalar_t__ loadedDictEnd; scalar_t__ dictID; int /*<<< orphan*/  stage; scalar_t__ nextToUpdate; scalar_t__ dictLimit; scalar_t__ lowLimit; int /*<<< orphan*/  frameContentSize; int /*<<< orphan*/  params; scalar_t__ base; scalar_t__ nextSrc; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U64 ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int ZSTD_REP_NUM ; 
 int /*<<< orphan*/  ZSTDcs_init ; 
 int /*<<< orphan*/ * repStartValue ; 
 int /*<<< orphan*/  xxh64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_continueCCtx(ZSTD_CCtx *cctx, ZSTD_parameters params, U64 frameContentSize)
{
	U32 const end = (U32)(cctx->nextSrc - cctx->base);
	cctx->params = params;
	cctx->frameContentSize = frameContentSize;
	cctx->lowLimit = end;
	cctx->dictLimit = end;
	cctx->nextToUpdate = end + 1;
	cctx->stage = ZSTDcs_init;
	cctx->dictID = 0;
	cctx->loadedDictEnd = 0;
	{
		int i;
		for (i = 0; i < ZSTD_REP_NUM; i++)
			cctx->rep[i] = repStartValue[i];
	}
	cctx->seqStore.litLengthSum = 0; /* force reset of btopt stats */
	xxh64_reset(&cctx->xxhState, 0);
	return 0;
}