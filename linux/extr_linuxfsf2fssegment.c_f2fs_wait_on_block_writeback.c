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
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_data_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

void f2fs_wait_on_block_writeback(struct f2fs_sb_info *sbi, block_t blkaddr)
{
	struct page *cpage;

	if (!is_valid_data_blkaddr(sbi, blkaddr))
		return;

	cpage = find_lock_page(META_MAPPING(sbi), blkaddr);
	if (cpage) {
		f2fs_wait_on_page_writeback(cpage, DATA, true);
		f2fs_put_page(cpage, 1);
	}
}