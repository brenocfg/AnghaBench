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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSE_CTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_V_F (size_t,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t FSE_CTABLE_SIZE_U32 (unsigned int,unsigned int) ; 
 unsigned int FSE_DEFAULT_TABLELOG ; 
 int FSE_MAX_SYMBOL_VALUE ; 
 size_t FSE_WKSP_SIZE_U32 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FSE_buildCTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,void*,size_t const) ; 
 int /*<<< orphan*/  FSE_compress_usingCTable (int /*<<< orphan*/ *,int,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSE_normalizeCount (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,size_t,unsigned int) ; 
 unsigned int FSE_optimalTableLog (unsigned int,size_t,unsigned int) ; 
 int /*<<< orphan*/  FSE_writeNCount (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  HIST_count_wksp (int /*<<< orphan*/ *,unsigned int*,void const*,size_t,unsigned int*) ; 
 size_t cSize ; 
 size_t maxCount ; 
 size_t nc_err ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t FSE_compress_wksp (void* dst, size_t dstSize, const void* src, size_t srcSize, unsigned maxSymbolValue, unsigned tableLog, void* workSpace, size_t wkspSize)
{
    BYTE* const ostart = (BYTE*) dst;
    BYTE* op = ostart;
    BYTE* const oend = ostart + dstSize;

    U32   count[FSE_MAX_SYMBOL_VALUE+1];
    S16   norm[FSE_MAX_SYMBOL_VALUE+1];
    FSE_CTable* CTable = (FSE_CTable*)workSpace;
    size_t const CTableSize = FSE_CTABLE_SIZE_U32(tableLog, maxSymbolValue);
    void* scratchBuffer = (void*)(CTable + CTableSize);
    size_t const scratchBufferSize = wkspSize - (CTableSize * sizeof(FSE_CTable));

    /* init conditions */
    if (wkspSize < FSE_WKSP_SIZE_U32(tableLog, maxSymbolValue)) return ERROR(tableLog_tooLarge);
    if (srcSize <= 1) return 0;  /* Not compressible */
    if (!maxSymbolValue) maxSymbolValue = FSE_MAX_SYMBOL_VALUE;
    if (!tableLog) tableLog = FSE_DEFAULT_TABLELOG;

    /* Scan input and build symbol stats */
    {   CHECK_V_F(maxCount, HIST_count_wksp(count, &maxSymbolValue, src, srcSize, (unsigned*)scratchBuffer) );
        if (maxCount == srcSize) return 1;   /* only a single symbol in src : rle */
        if (maxCount == 1) return 0;         /* each symbol present maximum once => not compressible */
        if (maxCount < (srcSize >> 7)) return 0;   /* Heuristic : not compressible enough */
    }

    tableLog = FSE_optimalTableLog(tableLog, srcSize, maxSymbolValue);
    CHECK_F( FSE_normalizeCount(norm, tableLog, count, srcSize, maxSymbolValue) );

    /* Write table description header */
    {   CHECK_V_F(nc_err, FSE_writeNCount(op, oend-op, norm, maxSymbolValue, tableLog) );
        op += nc_err;
    }

    /* Compress */
    CHECK_F( FSE_buildCTable_wksp(CTable, norm, maxSymbolValue, tableLog, scratchBuffer, scratchBufferSize) );
    {   CHECK_V_F(cSize, FSE_compress_usingCTable(op, oend - op, src, srcSize, CTable) );
        if (cSize == 0) return 0;   /* not enough space for compressed data */
        op += cSize;
    }

    /* check compressibility */
    if ( (size_t)(op-ostart) >= srcSize-1 ) return 0;

    return op-ostart;
}