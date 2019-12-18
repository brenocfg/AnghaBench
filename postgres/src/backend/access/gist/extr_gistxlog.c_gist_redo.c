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
#define  XLOG_GIST_DELETE 132 
#define  XLOG_GIST_PAGE_DELETE 131 
#define  XLOG_GIST_PAGE_REUSE 130 
#define  XLOG_GIST_PAGE_SPLIT 129 
#define  XLOG_GIST_PAGE_UPDATE 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gistRedoDeleteRecord (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistRedoPageDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistRedoPageReuse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistRedoPageSplitRecord (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistRedoPageUpdateRecord (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opCtx ; 

void
gist_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	MemoryContext oldCxt;

	/*
	 * GiST indexes do not require any conflict processing. NB: If we ever
	 * implement a similar optimization we have in b-tree, and remove killed
	 * tuples outside VACUUM, we'll need to handle that here.
	 */

	oldCxt = MemoryContextSwitchTo(opCtx);
	switch (info)
	{
		case XLOG_GIST_PAGE_UPDATE:
			gistRedoPageUpdateRecord(record);
			break;
		case XLOG_GIST_DELETE:
			gistRedoDeleteRecord(record);
			break;
		case XLOG_GIST_PAGE_REUSE:
			gistRedoPageReuse(record);
			break;
		case XLOG_GIST_PAGE_SPLIT:
			gistRedoPageSplitRecord(record);
			break;
		case XLOG_GIST_PAGE_DELETE:
			gistRedoPageDelete(record);
			break;
		default:
			elog(PANIC, "gist_redo: unknown op code %u", info);
	}

	MemoryContextSwitchTo(oldCxt);
	MemoryContextReset(opCtx);
}