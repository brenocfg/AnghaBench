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
#define  XLOG_HEAP2_CLEAN 135 
#define  XLOG_HEAP2_CLEANUP_INFO 134 
#define  XLOG_HEAP2_FREEZE_PAGE 133 
#define  XLOG_HEAP2_LOCK_UPDATED 132 
#define  XLOG_HEAP2_MULTI_INSERT 131 
#define  XLOG_HEAP2_NEW_CID 130 
#define  XLOG_HEAP2_REWRITE 129 
#define  XLOG_HEAP2_VISIBLE 128 
 int XLOG_HEAP_OPMASK ; 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  heap_xlog_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_cleanup_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_freeze_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_lock_updated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_logical_rewrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_multi_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_xlog_visible (int /*<<< orphan*/ *) ; 

void
heap2_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info & XLOG_HEAP_OPMASK)
	{
		case XLOG_HEAP2_CLEAN:
			heap_xlog_clean(record);
			break;
		case XLOG_HEAP2_FREEZE_PAGE:
			heap_xlog_freeze_page(record);
			break;
		case XLOG_HEAP2_CLEANUP_INFO:
			heap_xlog_cleanup_info(record);
			break;
		case XLOG_HEAP2_VISIBLE:
			heap_xlog_visible(record);
			break;
		case XLOG_HEAP2_MULTI_INSERT:
			heap_xlog_multi_insert(record);
			break;
		case XLOG_HEAP2_LOCK_UPDATED:
			heap_xlog_lock_updated(record);
			break;
		case XLOG_HEAP2_NEW_CID:

			/*
			 * Nothing to do on a real replay, only used during logical
			 * decoding.
			 */
			break;
		case XLOG_HEAP2_REWRITE:
			heap_xlog_logical_rewrite(record);
			break;
		default:
			elog(PANIC, "heap2_redo: unknown op code %u", info);
	}
}