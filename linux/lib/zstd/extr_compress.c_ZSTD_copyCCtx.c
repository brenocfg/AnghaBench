#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ strategy; int chainLog; size_t hashLog; } ;
struct TYPE_9__ {int contentSizeFlag; } ;
struct TYPE_11__ {TYPE_2__ cParams; TYPE_1__ fParams; } ;
typedef  TYPE_3__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_12__ {scalar_t__ stage; size_t hashLog3; int /*<<< orphan*/ * hufTable; scalar_t__ flagStaticHufTable; int /*<<< orphan*/ * offcodeCTable; int /*<<< orphan*/ * matchlengthCTable; int /*<<< orphan*/ * litlengthCTable; scalar_t__ flagStaticTables; int /*<<< orphan*/  dictID; int /*<<< orphan*/  loadedDictEnd; int /*<<< orphan*/  lowLimit; int /*<<< orphan*/  dictLimit; int /*<<< orphan*/  dictBase; int /*<<< orphan*/  base; int /*<<< orphan*/  nextSrc; int /*<<< orphan*/  nextToUpdate3; int /*<<< orphan*/  nextToUpdate; int /*<<< orphan*/ * workSpace; TYPE_3__ params; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_4__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_fast ; 
 int /*<<< orphan*/  ZSTD_resetCCtx_advanced (TYPE_4__*,TYPE_3__,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDcrp_noMemset ; 
 scalar_t__ ZSTDcs_init ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  stage_wrong ; 

size_t ZSTD_copyCCtx(ZSTD_CCtx *dstCCtx, const ZSTD_CCtx *srcCCtx, unsigned long long pledgedSrcSize)
{
	if (srcCCtx->stage != ZSTDcs_init)
		return ERROR(stage_wrong);

	memcpy(&dstCCtx->customMem, &srcCCtx->customMem, sizeof(ZSTD_customMem));
	{
		ZSTD_parameters params = srcCCtx->params;
		params.fParams.contentSizeFlag = (pledgedSrcSize > 0);
		ZSTD_resetCCtx_advanced(dstCCtx, params, pledgedSrcSize, ZSTDcrp_noMemset);
	}

	/* copy tables */
	{
		size_t const chainSize = (srcCCtx->params.cParams.strategy == ZSTD_fast) ? 0 : (1 << srcCCtx->params.cParams.chainLog);
		size_t const hSize = ((size_t)1) << srcCCtx->params.cParams.hashLog;
		size_t const h3Size = (size_t)1 << srcCCtx->hashLog3;
		size_t const tableSpace = (chainSize + hSize + h3Size) * sizeof(U32);
		memcpy(dstCCtx->workSpace, srcCCtx->workSpace, tableSpace);
	}

	/* copy dictionary offsets */
	dstCCtx->nextToUpdate = srcCCtx->nextToUpdate;
	dstCCtx->nextToUpdate3 = srcCCtx->nextToUpdate3;
	dstCCtx->nextSrc = srcCCtx->nextSrc;
	dstCCtx->base = srcCCtx->base;
	dstCCtx->dictBase = srcCCtx->dictBase;
	dstCCtx->dictLimit = srcCCtx->dictLimit;
	dstCCtx->lowLimit = srcCCtx->lowLimit;
	dstCCtx->loadedDictEnd = srcCCtx->loadedDictEnd;
	dstCCtx->dictID = srcCCtx->dictID;

	/* copy entropy tables */
	dstCCtx->flagStaticTables = srcCCtx->flagStaticTables;
	dstCCtx->flagStaticHufTable = srcCCtx->flagStaticHufTable;
	if (srcCCtx->flagStaticTables) {
		memcpy(dstCCtx->litlengthCTable, srcCCtx->litlengthCTable, sizeof(dstCCtx->litlengthCTable));
		memcpy(dstCCtx->matchlengthCTable, srcCCtx->matchlengthCTable, sizeof(dstCCtx->matchlengthCTable));
		memcpy(dstCCtx->offcodeCTable, srcCCtx->offcodeCTable, sizeof(dstCCtx->offcodeCTable));
	}
	if (srcCCtx->flagStaticHufTable) {
		memcpy(dstCCtx->hufTable, srcCCtx->hufTable, 256 * 4);
	}

	return 0;
}