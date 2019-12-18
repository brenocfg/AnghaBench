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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
#define  XLOG_SPGIST_ADD_LEAF 135 
#define  XLOG_SPGIST_ADD_NODE 134 
#define  XLOG_SPGIST_MOVE_LEAFS 133 
#define  XLOG_SPGIST_PICKSPLIT 132 
#define  XLOG_SPGIST_SPLIT_TUPLE 131 
#define  XLOG_SPGIST_VACUUM_LEAF 130 
#define  XLOG_SPGIST_VACUUM_REDIRECT 129 
#define  XLOG_SPGIST_VACUUM_ROOT 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  opCtx ; 
 int /*<<< orphan*/  spgRedoAddLeaf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoAddNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoMoveLeafs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoPickSplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoSplitTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoVacuumLeaf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoVacuumRedirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgRedoVacuumRoot (int /*<<< orphan*/ *) ; 

void
spg_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	MemoryContext oldCxt;

	oldCxt = MemoryContextSwitchTo(opCtx);
	switch (info)
	{
		case XLOG_SPGIST_ADD_LEAF:
			spgRedoAddLeaf(record);
			break;
		case XLOG_SPGIST_MOVE_LEAFS:
			spgRedoMoveLeafs(record);
			break;
		case XLOG_SPGIST_ADD_NODE:
			spgRedoAddNode(record);
			break;
		case XLOG_SPGIST_SPLIT_TUPLE:
			spgRedoSplitTuple(record);
			break;
		case XLOG_SPGIST_PICKSPLIT:
			spgRedoPickSplit(record);
			break;
		case XLOG_SPGIST_VACUUM_LEAF:
			spgRedoVacuumLeaf(record);
			break;
		case XLOG_SPGIST_VACUUM_ROOT:
			spgRedoVacuumRoot(record);
			break;
		case XLOG_SPGIST_VACUUM_REDIRECT:
			spgRedoVacuumRedirect(record);
			break;
		default:
			elog(PANIC, "spg_redo: unknown op code %u", info);
	}

	MemoryContextSwitchTo(oldCxt);
	MemoryContextReset(opCtx);
}