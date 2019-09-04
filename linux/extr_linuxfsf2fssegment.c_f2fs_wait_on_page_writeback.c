#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

void f2fs_wait_on_page_writeback(struct page *page,
				enum page_type type, bool ordered)
{
	if (PageWriteback(page)) {
		struct f2fs_sb_info *sbi = F2FS_P_SB(page);

		f2fs_submit_merged_write_cond(sbi, page->mapping->host,
						0, page->index, type);
		if (ordered)
			wait_on_page_writeback(page);
		else
			wait_for_stable_page(page);
	}
}