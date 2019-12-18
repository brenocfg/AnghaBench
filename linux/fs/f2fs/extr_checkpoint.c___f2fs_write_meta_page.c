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
struct writeback_control {scalar_t__ for_reclaim; } ;
struct page {scalar_t__ index; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int /*<<< orphan*/  F2FS_DIRTY_META ; 
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 scalar_t__ GET_SUM_BLOCK (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 int /*<<< orphan*/  dec_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_do_write_meta_page (struct f2fs_sb_info*,struct page*,int) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  trace_f2fs_writepage (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int __f2fs_write_meta_page(struct page *page,
				struct writeback_control *wbc,
				enum iostat_type io_type)
{
	struct f2fs_sb_info *sbi = F2FS_P_SB(page);

	trace_f2fs_writepage(page, META);

	if (unlikely(f2fs_cp_error(sbi)))
		goto redirty_out;
	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto redirty_out;
	if (wbc->for_reclaim && page->index < GET_SUM_BLOCK(sbi, 0))
		goto redirty_out;

	f2fs_do_write_meta_page(sbi, page, io_type);
	dec_page_count(sbi, F2FS_DIRTY_META);

	if (wbc->for_reclaim)
		f2fs_submit_merged_write_cond(sbi, NULL, page, 0, META);

	unlock_page(page);

	if (unlikely(f2fs_cp_error(sbi)))
		f2fs_submit_merged_write(sbi, META);

	return 0;

redirty_out:
	redirty_page_for_writepage(wbc, page);
	return AOP_WRITEPAGE_ACTIVATE;
}