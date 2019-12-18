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
#define  XLOG_GIN_CREATE_PTREE 136 
#define  XLOG_GIN_DELETE_LISTPAGE 135 
#define  XLOG_GIN_DELETE_PAGE 134 
#define  XLOG_GIN_INSERT 133 
#define  XLOG_GIN_INSERT_LISTPAGE 132 
#define  XLOG_GIN_SPLIT 131 
#define  XLOG_GIN_UPDATE_META_PAGE 130 
#define  XLOG_GIN_VACUUM_DATA_LEAF_PAGE 129 
#define  XLOG_GIN_VACUUM_PAGE 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ginRedoCreatePTree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoDeleteListPages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoDeletePage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoInsert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoInsertListPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoSplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoUpdateMetapage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoVacuumDataLeafPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginRedoVacuumPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opCtx ; 

void
gin_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	MemoryContext oldCtx;

	/*
	 * GIN indexes do not require any conflict processing. NB: If we ever
	 * implement a similar optimization as we have in b-tree, and remove
	 * killed tuples outside VACUUM, we'll need to handle that here.
	 */

	oldCtx = MemoryContextSwitchTo(opCtx);
	switch (info)
	{
		case XLOG_GIN_CREATE_PTREE:
			ginRedoCreatePTree(record);
			break;
		case XLOG_GIN_INSERT:
			ginRedoInsert(record);
			break;
		case XLOG_GIN_SPLIT:
			ginRedoSplit(record);
			break;
		case XLOG_GIN_VACUUM_PAGE:
			ginRedoVacuumPage(record);
			break;
		case XLOG_GIN_VACUUM_DATA_LEAF_PAGE:
			ginRedoVacuumDataLeafPage(record);
			break;
		case XLOG_GIN_DELETE_PAGE:
			ginRedoDeletePage(record);
			break;
		case XLOG_GIN_UPDATE_META_PAGE:
			ginRedoUpdateMetapage(record);
			break;
		case XLOG_GIN_INSERT_LISTPAGE:
			ginRedoInsertListPage(record);
			break;
		case XLOG_GIN_DELETE_LISTPAGE:
			ginRedoDeleteListPages(record);
			break;
		default:
			elog(PANIC, "gin_redo: unknown op code %u", info);
	}
	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(opCtx);
}