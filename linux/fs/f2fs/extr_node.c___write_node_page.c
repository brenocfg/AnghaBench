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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_reclaim; } ;
struct page {scalar_t__ index; } ;
struct node_info {scalar_t__ blk_addr; } ;
struct f2fs_sb_info {int /*<<< orphan*/  node_write; } ;
struct f2fs_io_info {int op_flags; int submitted; int io_type; scalar_t__ old_blkaddr; int /*<<< orphan*/  new_blkaddr; struct writeback_control* io_wbc; int /*<<< orphan*/ * encrypted_page; struct page* page; int /*<<< orphan*/  op; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; struct f2fs_sb_info* sbi; } ;
typedef  scalar_t__ nid_t ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 scalar_t__ IS_DNODE (struct page*) ; 
 int /*<<< orphan*/  NOBARRIER ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ NULL_ADDR ; 
 int REQ_FUA ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ WB_SYNC_NONE ; 
 scalar_t__ __is_valid_data_blkaddr (scalar_t__) ; 
 int /*<<< orphan*/  dec_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 unsigned int f2fs_add_fsync_node_entry (struct f2fs_sb_info*,struct page*) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_do_write_node_page (scalar_t__,struct f2fs_io_info*) ; 
 scalar_t__ f2fs_get_node_info (struct f2fs_sb_info*,scalar_t__,struct node_info*) ; 
 scalar_t__ f2fs_in_warm_node_list (struct f2fs_sb_info*,struct page*) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 scalar_t__ is_cold_node (struct page*) ; 
 int /*<<< orphan*/  is_fsync_dnode (struct page*) ; 
 int is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ nid_of_node (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_node_addr (struct f2fs_sb_info*,struct node_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_writepage (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int wbc_to_write_flags (struct writeback_control*) ; 

__attribute__((used)) static int __write_node_page(struct page *page, bool atomic, bool *submitted,
				struct writeback_control *wbc, bool do_balance,
				enum iostat_type io_type, unsigned int *seq_id)
{
	struct f2fs_sb_info *sbi = F2FS_P_SB(page);
	nid_t nid;
	struct node_info ni;
	struct f2fs_io_info fio = {
		.sbi = sbi,
		.ino = ino_of_node(page),
		.type = NODE,
		.op = REQ_OP_WRITE,
		.op_flags = wbc_to_write_flags(wbc),
		.page = page,
		.encrypted_page = NULL,
		.submitted = false,
		.io_type = io_type,
		.io_wbc = wbc,
	};
	unsigned int seq;

	trace_f2fs_writepage(page, NODE);

	if (unlikely(f2fs_cp_error(sbi)))
		goto redirty_out;

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto redirty_out;

	if (!is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			wbc->sync_mode == WB_SYNC_NONE &&
			IS_DNODE(page) && is_cold_node(page))
		goto redirty_out;

	/* get old block addr of this node page */
	nid = nid_of_node(page);
	f2fs_bug_on(sbi, page->index != nid);

	if (f2fs_get_node_info(sbi, nid, &ni))
		goto redirty_out;

	if (wbc->for_reclaim) {
		if (!down_read_trylock(&sbi->node_write))
			goto redirty_out;
	} else {
		down_read(&sbi->node_write);
	}

	/* This page is already truncated */
	if (unlikely(ni.blk_addr == NULL_ADDR)) {
		ClearPageUptodate(page);
		dec_page_count(sbi, F2FS_DIRTY_NODES);
		up_read(&sbi->node_write);
		unlock_page(page);
		return 0;
	}

	if (__is_valid_data_blkaddr(ni.blk_addr) &&
		!f2fs_is_valid_blkaddr(sbi, ni.blk_addr,
					DATA_GENERIC_ENHANCE)) {
		up_read(&sbi->node_write);
		goto redirty_out;
	}

	if (atomic && !test_opt(sbi, NOBARRIER))
		fio.op_flags |= REQ_PREFLUSH | REQ_FUA;

	set_page_writeback(page);
	ClearPageError(page);

	if (f2fs_in_warm_node_list(sbi, page)) {
		seq = f2fs_add_fsync_node_entry(sbi, page);
		if (seq_id)
			*seq_id = seq;
	}

	fio.old_blkaddr = ni.blk_addr;
	f2fs_do_write_node_page(nid, &fio);
	set_node_addr(sbi, &ni, fio.new_blkaddr, is_fsync_dnode(page));
	dec_page_count(sbi, F2FS_DIRTY_NODES);
	up_read(&sbi->node_write);

	if (wbc->for_reclaim) {
		f2fs_submit_merged_write_cond(sbi, NULL, page, 0, NODE);
		submitted = NULL;
	}

	unlock_page(page);

	if (unlikely(f2fs_cp_error(sbi))) {
		f2fs_submit_merged_write(sbi, NODE);
		submitted = NULL;
	}
	if (submitted)
		*submitted = fio.submitted;

	if (do_balance)
		f2fs_balance_fs(sbi, false);
	return 0;

redirty_out:
	redirty_page_for_writepage(wbc, page);
	return AOP_WRITEPAGE_ACTIVATE;
}