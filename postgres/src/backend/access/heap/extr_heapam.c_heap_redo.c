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

/* Variables and functions */
 int /*<<< orphan*/  PANIC ; 
#define  XLOG_HEAP_CONFIRM 135 
#define  XLOG_HEAP_DELETE 134 
#define  XLOG_HEAP_HOT_UPDATE 133 
#define  XLOG_HEAP_INPLACE 132 
#define  XLOG_HEAP_INSERT 131 
#define  XLOG_HEAP_LOCK 130 
 int XLOG_HEAP_OPMASK ; 
#define  XLOG_HEAP_TRUNCATE 129 
#define  XLOG_HEAP_UPDATE 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  heap_xlog_confirm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_inplace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_update (int /*<<< orphan*/ *,int) ; 

void
heap_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	/*
	 * These operations don't overwrite MVCC data so no conflict processing is
	 * required. The ones in heap2 rmgr do.
	 */

	switch (info & XLOG_HEAP_OPMASK)
	{
		case XLOG_HEAP_INSERT:
			heap_xlog_insert(record);
			break;
		case XLOG_HEAP_DELETE:
			heap_xlog_delete(record);
			break;
		case XLOG_HEAP_UPDATE:
			heap_xlog_update(record, false);
			break;
		case XLOG_HEAP_TRUNCATE:

			/*
			 * TRUNCATE is a no-op because the actions are already logged as
			 * SMGR WAL records.  TRUNCATE WAL record only exists for logical
			 * decoding.
			 */
			break;
		case XLOG_HEAP_HOT_UPDATE:
			heap_xlog_update(record, true);
			break;
		case XLOG_HEAP_CONFIRM:
			heap_xlog_confirm(record);
			break;
		case XLOG_HEAP_LOCK:
			heap_xlog_lock(record);
			break;
		case XLOG_HEAP_INPLACE:
			heap_xlog_inplace(record);
			break;
		default:
			elog(PANIC, "heap_redo: unknown op code %u", info);
	}
}