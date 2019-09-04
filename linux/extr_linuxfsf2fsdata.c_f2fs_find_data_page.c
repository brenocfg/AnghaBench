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
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 struct page* f2fs_get_read_data_page (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

struct page *f2fs_find_data_page(struct inode *inode, pgoff_t index)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page;

	page = find_get_page(mapping, index);
	if (page && PageUptodate(page))
		return page;
	f2fs_put_page(page, 0);

	page = f2fs_get_read_data_page(inode, index, 0, false);
	if (IS_ERR(page))
		return page;

	if (PageUptodate(page))
		return page;

	wait_on_page_locked(page);
	if (unlikely(!PageUptodate(page))) {
		f2fs_put_page(page, 0);
		return ERR_PTR(-EIO);
	}
	return page;
}