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
typedef  int /*<<< orphan*/  dtd ;
typedef  scalar_t__ U32 ;
struct TYPE_6__ {void* tableLog; scalar_t__ tableType; scalar_t__ maxTableLog; } ;
struct TYPE_5__ {void* nbBits; void* byte; } ;
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  TYPE_1__ HUF_DEltX2 ;
typedef  TYPE_2__ DTableDesc ;
typedef  void* BYTE ;

/* Variables and functions */
 int ALIGN (scalar_t__,int) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUF_STATIC_ASSERT (int) ; 
 scalar_t__ HUF_SYMBOLVALUE_MAX ; 
 scalar_t__ HUF_TABLELOG_ABSOLUTEMAX ; 
 TYPE_2__ HUF_getDTableDesc (int /*<<< orphan*/ *) ; 
 scalar_t__ HUF_isError (size_t) ; 
 size_t HUF_readStats_wksp (void**,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,void const*,size_t,void*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t HUF_readDTableX2_wksp(HUF_DTable *DTable, const void *src, size_t srcSize, void *workspace, size_t workspaceSize)
{
	U32 tableLog = 0;
	U32 nbSymbols = 0;
	size_t iSize;
	void *const dtPtr = DTable + 1;
	HUF_DEltX2 *const dt = (HUF_DEltX2 *)dtPtr;

	U32 *rankVal;
	BYTE *huffWeight;
	size_t spaceUsed32 = 0;

	rankVal = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_ABSOLUTEMAX + 1;
	huffWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX + 1, sizeof(U32)) >> 2;

	if ((spaceUsed32 << 2) > workspaceSize)
		return ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	HUF_STATIC_ASSERT(sizeof(DTableDesc) == sizeof(HUF_DTable));
	/* memset(huffWeight, 0, sizeof(huffWeight)); */ /* is not necessary, even though some analyzer complain ... */

	iSize = HUF_readStats_wksp(huffWeight, HUF_SYMBOLVALUE_MAX + 1, rankVal, &nbSymbols, &tableLog, src, srcSize, workspace, workspaceSize);
	if (HUF_isError(iSize))
		return iSize;

	/* Table header */
	{
		DTableDesc dtd = HUF_getDTableDesc(DTable);
		if (tableLog > (U32)(dtd.maxTableLog + 1))
			return ERROR(tableLog_tooLarge); /* DTable too small, Huffman tree cannot fit in */
		dtd.tableType = 0;
		dtd.tableLog = (BYTE)tableLog;
		memcpy(DTable, &dtd, sizeof(dtd));
	}

	/* Calculate starting value for each rank */
	{
		U32 n, nextRankStart = 0;
		for (n = 1; n < tableLog + 1; n++) {
			U32 const curr = nextRankStart;
			nextRankStart += (rankVal[n] << (n - 1));
			rankVal[n] = curr;
		}
	}

	/* fill DTable */
	{
		U32 n;
		for (n = 0; n < nbSymbols; n++) {
			U32 const w = huffWeight[n];
			U32 const length = (1 << w) >> 1;
			U32 u;
			HUF_DEltX2 D;
			D.byte = (BYTE)n;
			D.nbBits = (BYTE)(tableLog + 1 - w);
			for (u = rankVal[w]; u < rankVal[w] + length; u++)
				dt[u] = D;
			rankVal[w] += length;
		}
	}

	return iSize;
}