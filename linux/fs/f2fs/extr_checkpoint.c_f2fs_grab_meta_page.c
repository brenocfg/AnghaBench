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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  META ; 
 struct address_space* META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* f2fs_grab_cache_page (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 

struct page *f2fs_grab_meta_page(struct f2fs_sb_info *sbi, pgoff_t index)
{
	struct address_space *mapping = META_MAPPING(sbi);
	struct page *page = NULL;
repeat:
	page = f2fs_grab_cache_page(mapping, index, false);
	if (!page) {
		cond_resched();
		goto repeat;
	}
	f2fs_wait_on_page_writeback(page, META, true, true);
	if (!PageUptodate(page))
		SetPageUptodate(page);
	return page;
}