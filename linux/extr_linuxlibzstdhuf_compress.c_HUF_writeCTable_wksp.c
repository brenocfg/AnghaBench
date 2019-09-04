#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_3__ {size_t nbBits; } ;
typedef  TYPE_1__ HUF_CElt ;
typedef  int BYTE ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CHECK_V_F (int,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int HUF_SYMBOLVALUE_MAX ; 
 int HUF_TABLELOG_MAX ; 
 int /*<<< orphan*/  HUF_compressWeights_wksp (int*,size_t,int*,int,void*,size_t) ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int hSize ; 
 int /*<<< orphan*/  maxSymbolValue_tooLarge ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t HUF_writeCTable_wksp(void *dst, size_t maxDstSize, const HUF_CElt *CTable, U32 maxSymbolValue, U32 huffLog, void *workspace, size_t workspaceSize)
{
	BYTE *op = (BYTE *)dst;
	U32 n;

	BYTE *bitsToWeight;
	BYTE *huffWeight;
	size_t spaceUsed32 = 0;

	bitsToWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_TABLELOG_MAX + 1, sizeof(U32)) >> 2;
	huffWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX, sizeof(U32)) >> 2;

	if ((spaceUsed32 << 2) > workspaceSize)
		return ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* check conditions */
	if (maxSymbolValue > HUF_SYMBOLVALUE_MAX)
		return ERROR(maxSymbolValue_tooLarge);

	/* convert to weight */
	bitsToWeight[0] = 0;
	for (n = 1; n < huffLog + 1; n++)
		bitsToWeight[n] = (BYTE)(huffLog + 1 - n);
	for (n = 0; n < maxSymbolValue; n++)
		huffWeight[n] = bitsToWeight[CTable[n].nbBits];

	/* attempt weights compression by FSE */
	{
		CHECK_V_F(hSize, HUF_compressWeights_wksp(op + 1, maxDstSize - 1, huffWeight, maxSymbolValue, workspace, workspaceSize));
		if ((hSize > 1) & (hSize < maxSymbolValue / 2)) { /* FSE compressed */
			op[0] = (BYTE)hSize;
			return hSize + 1;
		}
	}

	/* write raw values as 4-bits (max : 15) */
	if (maxSymbolValue > (256 - 128))
		return ERROR(GENERIC); /* should not happen : likely means source cannot be compressed */
	if (((maxSymbolValue + 1) / 2) + 1 > maxDstSize)
		return ERROR(dstSize_tooSmall); /* not enough space within dst buffer */
	op[0] = (BYTE)(128 /*special case*/ + (maxSymbolValue - 1));
	huffWeight[maxSymbolValue] = 0; /* to be sure it doesn't cause msan issue in final combination */
	for (n = 0; n < maxSymbolValue; n += 2)
		op[(n / 2) + 1] = (BYTE)((huffWeight[n] << 4) + huffWeight[n + 1]);
	return ((maxSymbolValue + 1) / 2) + 1;
}