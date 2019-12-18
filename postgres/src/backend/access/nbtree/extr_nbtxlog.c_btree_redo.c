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
#define  XLOG_BTREE_DELETE 140 
#define  XLOG_BTREE_INSERT_LEAF 139 
#define  XLOG_BTREE_INSERT_META 138 
#define  XLOG_BTREE_INSERT_UPPER 137 
#define  XLOG_BTREE_MARK_PAGE_HALFDEAD 136 
#define  XLOG_BTREE_META_CLEANUP 135 
#define  XLOG_BTREE_NEWROOT 134 
#define  XLOG_BTREE_REUSE_PAGE 133 
#define  XLOG_BTREE_SPLIT_L 132 
#define  XLOG_BTREE_SPLIT_R 131 
#define  XLOG_BTREE_UNLINK_PAGE 130 
#define  XLOG_BTREE_UNLINK_PAGE_META 129 
#define  XLOG_BTREE_VACUUM 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_restore_meta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btree_xlog_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_insert (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_mark_page_halfdead (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_newroot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_reuse_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_split (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_unlink_page (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_xlog_vacuum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
btree_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_BTREE_INSERT_LEAF:
			btree_xlog_insert(true, false, record);
			break;
		case XLOG_BTREE_INSERT_UPPER:
			btree_xlog_insert(false, false, record);
			break;
		case XLOG_BTREE_INSERT_META:
			btree_xlog_insert(false, true, record);
			break;
		case XLOG_BTREE_SPLIT_L:
			btree_xlog_split(true, record);
			break;
		case XLOG_BTREE_SPLIT_R:
			btree_xlog_split(false, record);
			break;
		case XLOG_BTREE_VACUUM:
			btree_xlog_vacuum(record);
			break;
		case XLOG_BTREE_DELETE:
			btree_xlog_delete(record);
			break;
		case XLOG_BTREE_MARK_PAGE_HALFDEAD:
			btree_xlog_mark_page_halfdead(info, record);
			break;
		case XLOG_BTREE_UNLINK_PAGE:
		case XLOG_BTREE_UNLINK_PAGE_META:
			btree_xlog_unlink_page(info, record);
			break;
		case XLOG_BTREE_NEWROOT:
			btree_xlog_newroot(record);
			break;
		case XLOG_BTREE_REUSE_PAGE:
			btree_xlog_reuse_page(record);
			break;
		case XLOG_BTREE_META_CLEANUP:
			_bt_restore_meta(record, 0);
			break;
		default:
			elog(PANIC, "btree_redo: unknown op code %u", info);
	}
}