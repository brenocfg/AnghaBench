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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ENOENT ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int) ; 
 struct page* f2fs_get_lock_data_page (struct inode*,int,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 struct page* find_lock_page (struct address_space*,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,int,int) ; 

__attribute__((used)) static int truncate_partial_data_page(struct inode *inode, u64 from,
								bool cache_only)
{
	loff_t offset = from & (PAGE_SIZE - 1);
	pgoff_t index = from >> PAGE_SHIFT;
	struct address_space *mapping = inode->i_mapping;
	struct page *page;

	if (!offset && !cache_only)
		return 0;

	if (cache_only) {
		page = find_lock_page(mapping, index);
		if (page && PageUptodate(page))
			goto truncate_out;
		f2fs_put_page(page, 1);
		return 0;
	}

	page = f2fs_get_lock_data_page(inode, index, true);
	if (IS_ERR(page))
		return PTR_ERR(page) == -ENOENT ? 0 : PTR_ERR(page);
truncate_out:
	f2fs_wait_on_page_writeback(page, DATA, true, true);
	zero_user(page, offset, PAGE_SIZE - offset);

	/* An encrypted inode should have a key and truncate the last page. */
	f2fs_bug_on(F2FS_I_SB(inode), cache_only && IS_ENCRYPTED(inode));
	if (!cache_only)
		set_page_dirty(page);
	f2fs_put_page(page, 1);
	return 0;
}