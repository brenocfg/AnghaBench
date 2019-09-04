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
typedef  int symbolEncodingType_e ;
typedef  int /*<<< orphan*/  const U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  FSE_decode_t4 ;
typedef  int /*<<< orphan*/  FSE_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_buildDTable_rle (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  FSE_buildDTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void*,size_t) ; 
 int /*<<< orphan*/  FSE_isError (size_t const) ; 
 size_t FSE_readNCount (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  MaxSeq ; 
 int /*<<< orphan*/  corruption_detected ; 
#define  set_basic 131 
#define  set_compressed 130 
#define  set_repeat 129 
#define  set_rle 128 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_buildSeqTable(FSE_DTable *DTableSpace, const FSE_DTable **DTablePtr, symbolEncodingType_e type, U32 max, U32 maxLog, const void *src,
				 size_t srcSize, const FSE_decode_t4 *defaultTable, U32 flagRepeatTable, void *workspace, size_t workspaceSize)
{
	const void *const tmpPtr = defaultTable; /* bypass strict aliasing */
	switch (type) {
	case set_rle:
		if (!srcSize)
			return ERROR(srcSize_wrong);
		if ((*(const BYTE *)src) > max)
			return ERROR(corruption_detected);
		FSE_buildDTable_rle(DTableSpace, *(const BYTE *)src);
		*DTablePtr = DTableSpace;
		return 1;
	case set_basic: *DTablePtr = (const FSE_DTable *)tmpPtr; return 0;
	case set_repeat:
		if (!flagRepeatTable)
			return ERROR(corruption_detected);
		return 0;
	default: /* impossible */
	case set_compressed: {
		U32 tableLog;
		S16 *norm = (S16 *)workspace;
		size_t const spaceUsed32 = ALIGN(sizeof(S16) * (MaxSeq + 1), sizeof(U32)) >> 2;

		if ((spaceUsed32 << 2) > workspaceSize)
			return ERROR(GENERIC);
		workspace = (U32 *)workspace + spaceUsed32;
		workspaceSize -= (spaceUsed32 << 2);
		{
			size_t const headerSize = FSE_readNCount(norm, &max, &tableLog, src, srcSize);
			if (FSE_isError(headerSize))
				return ERROR(corruption_detected);
			if (tableLog > maxLog)
				return ERROR(corruption_detected);
			FSE_buildDTable_wksp(DTableSpace, norm, max, tableLog, workspace, workspaceSize);
			*DTablePtr = DTableSpace;
			return headerSize;
		}
	}
	}
}