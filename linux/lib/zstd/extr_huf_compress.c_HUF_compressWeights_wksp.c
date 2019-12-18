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
typedef  int U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSE_CTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_V_F (size_t,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ FSE_CTABLE_SIZE_U32 (int,int) ; 
 int /*<<< orphan*/  FSE_buildCTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,void*,size_t) ; 
 int /*<<< orphan*/  FSE_compress_usingCTable (int /*<<< orphan*/ *,int,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSE_count_simple (int*,int*,void const*,size_t) ; 
 int /*<<< orphan*/  FSE_normalizeCount (int /*<<< orphan*/ *,int,int*,size_t,int) ; 
 int FSE_optimalTableLog (int,size_t,int) ; 
 int /*<<< orphan*/  FSE_writeNCount (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  HUF_STATIC_ASSERT (int) ; 
 int HUF_TABLELOG_MAX ; 
 int MAX_FSE_TABLELOG_FOR_HUFF_HEADER ; 
 size_t cSize ; 
 size_t hSize ; 
 size_t maxCount ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t HUF_compressWeights_wksp(void *dst, size_t dstSize, const void *weightTable, size_t wtSize, void *workspace, size_t workspaceSize)
{
	BYTE *const ostart = (BYTE *)dst;
	BYTE *op = ostart;
	BYTE *const oend = ostart + dstSize;

	U32 maxSymbolValue = HUF_TABLELOG_MAX;
	U32 tableLog = MAX_FSE_TABLELOG_FOR_HUFF_HEADER;

	FSE_CTable *CTable;
	U32 *count;
	S16 *norm;
	size_t spaceUsed32 = 0;

	HUF_STATIC_ASSERT(sizeof(FSE_CTable) == sizeof(U32));

	CTable = (FSE_CTable *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += FSE_CTABLE_SIZE_U32(MAX_FSE_TABLELOG_FOR_HUFF_HEADER, HUF_TABLELOG_MAX);
	count = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_MAX + 1;
	norm = (S16 *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(sizeof(S16) * (HUF_TABLELOG_MAX + 1), sizeof(U32)) >> 2;

	if ((spaceUsed32 << 2) > workspaceSize)
		return ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* init conditions */
	if (wtSize <= 1)
		return 0; /* Not compressible */

	/* Scan input and build symbol stats */
	{
		CHECK_V_F(maxCount, FSE_count_simple(count, &maxSymbolValue, weightTable, wtSize));
		if (maxCount == wtSize)
			return 1; /* only a single symbol in src : rle */
		if (maxCount == 1)
			return 0; /* each symbol present maximum once => not compressible */
	}

	tableLog = FSE_optimalTableLog(tableLog, wtSize, maxSymbolValue);
	CHECK_F(FSE_normalizeCount(norm, tableLog, count, wtSize, maxSymbolValue));

	/* Write table description header */
	{
		CHECK_V_F(hSize, FSE_writeNCount(op, oend - op, norm, maxSymbolValue, tableLog));
		op += hSize;
	}

	/* Compress */
	CHECK_F(FSE_buildCTable_wksp(CTable, norm, maxSymbolValue, tableLog, workspace, workspaceSize));
	{
		CHECK_V_F(cSize, FSE_compress_usingCTable(op, oend - op, weightTable, wtSize, CTable));
		if (cSize == 0)
			return 0; /* not enough space for compressed data */
		op += cSize;
	}

	return op - ostart;
}