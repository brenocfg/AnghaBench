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
struct f2fs_sb_info {int dummy; } ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

void f2fs_wait_on_page_writeback(struct page *page,
				enum page_type type, bool ordered, bool locked)
{
	if (PageWriteback(page)) {
		struct f2fs_sb_info *sbi = F2FS_P_SB(page);

		f2fs_submit_merged_write_cond(sbi, NULL, page, 0, type);
		if (ordered) {
			wait_on_page_writeback(page);
			f2fs_bug_on(sbi, locked && PageWriteback(page));
		} else {
			wait_for_stable_page(page);
		}
	}
}