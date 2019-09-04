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
struct page {int dummy; } ;
struct f2fs_summary_block {int /*<<< orphan*/  footer; int /*<<< orphan*/ * entries; int /*<<< orphan*/  journal; } ;
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  curseg_mutex; int /*<<< orphan*/  journal_rwsem; int /*<<< orphan*/ * journal; struct f2fs_summary_block* sum_blk; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SUM_ENTRY_SIZE ; 
 int /*<<< orphan*/  SUM_FOOTER_SIZE ; 
 int /*<<< orphan*/  SUM_JOURNAL_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct page* f2fs_grab_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct f2fs_summary_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_current_sum_page(struct f2fs_sb_info *sbi,
						int type, block_t blk_addr)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);
	struct page *page = f2fs_grab_meta_page(sbi, blk_addr);
	struct f2fs_summary_block *src = curseg->sum_blk;
	struct f2fs_summary_block *dst;

	dst = (struct f2fs_summary_block *)page_address(page);
	memset(dst, 0, PAGE_SIZE);

	mutex_lock(&curseg->curseg_mutex);

	down_read(&curseg->journal_rwsem);
	memcpy(&dst->journal, curseg->journal, SUM_JOURNAL_SIZE);
	up_read(&curseg->journal_rwsem);

	memcpy(dst->entries, src->entries, SUM_ENTRY_SIZE);
	memcpy(&dst->footer, &src->footer, SUM_FOOTER_SIZE);

	mutex_unlock(&curseg->curseg_mutex);

	set_page_dirty(page);
	f2fs_put_page(page, 1);
}