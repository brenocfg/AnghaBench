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
#define  XLOG_HASH_ADD_OVFL_PAGE 140 
#define  XLOG_HASH_DELETE 139 
#define  XLOG_HASH_INIT_BITMAP_PAGE 138 
#define  XLOG_HASH_INIT_META_PAGE 137 
#define  XLOG_HASH_INSERT 136 
#define  XLOG_HASH_MOVE_PAGE_CONTENTS 135 
#define  XLOG_HASH_SPLIT_ALLOCATE_PAGE 134 
#define  XLOG_HASH_SPLIT_CLEANUP 133 
#define  XLOG_HASH_SPLIT_COMPLETE 132 
#define  XLOG_HASH_SPLIT_PAGE 131 
#define  XLOG_HASH_SQUEEZE_PAGE 130 
#define  XLOG_HASH_UPDATE_META_PAGE 129 
#define  XLOG_HASH_VACUUM_ONE_PAGE 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hash_xlog_add_ovfl_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_init_bitmap_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_init_meta_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_move_page_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_split_allocate_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_split_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_split_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_split_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_squeeze_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_update_meta_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_xlog_vacuum_one_page (int /*<<< orphan*/ *) ; 

void
hash_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_HASH_INIT_META_PAGE:
			hash_xlog_init_meta_page(record);
			break;
		case XLOG_HASH_INIT_BITMAP_PAGE:
			hash_xlog_init_bitmap_page(record);
			break;
		case XLOG_HASH_INSERT:
			hash_xlog_insert(record);
			break;
		case XLOG_HASH_ADD_OVFL_PAGE:
			hash_xlog_add_ovfl_page(record);
			break;
		case XLOG_HASH_SPLIT_ALLOCATE_PAGE:
			hash_xlog_split_allocate_page(record);
			break;
		case XLOG_HASH_SPLIT_PAGE:
			hash_xlog_split_page(record);
			break;
		case XLOG_HASH_SPLIT_COMPLETE:
			hash_xlog_split_complete(record);
			break;
		case XLOG_HASH_MOVE_PAGE_CONTENTS:
			hash_xlog_move_page_contents(record);
			break;
		case XLOG_HASH_SQUEEZE_PAGE:
			hash_xlog_squeeze_page(record);
			break;
		case XLOG_HASH_DELETE:
			hash_xlog_delete(record);
			break;
		case XLOG_HASH_SPLIT_CLEANUP:
			hash_xlog_split_cleanup(record);
			break;
		case XLOG_HASH_UPDATE_META_PAGE:
			hash_xlog_update_meta_page(record);
			break;
		case XLOG_HASH_VACUUM_ONE_PAGE:
			hash_xlog_vacuum_one_page(record);
			break;
		default:
			elog(PANIC, "hash_redo: unknown op code %u", info);
	}
}