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
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* f2fs_grab_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void f2fs_update_meta_page(struct f2fs_sb_info *sbi,
					void *src, block_t blk_addr)
{
	struct page *page = f2fs_grab_meta_page(sbi, blk_addr);

	memcpy(page_address(page), src, PAGE_SIZE);
	set_page_dirty(page);
	f2fs_put_page(page, 1);
}