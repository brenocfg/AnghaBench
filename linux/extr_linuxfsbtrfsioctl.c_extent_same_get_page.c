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
struct page {scalar_t__ mapping; } ;
struct inode {scalar_t__ i_mapping; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 struct page* ERR_PTR (int) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int btrfs_readpage (int /*<<< orphan*/ *,struct page*) ; 
 struct page* grab_cache_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static struct page *extent_same_get_page(struct inode *inode, pgoff_t index)
{
	struct page *page;

	page = grab_cache_page(inode->i_mapping, index);
	if (!page)
		return ERR_PTR(-ENOMEM);

	if (!PageUptodate(page)) {
		int ret;

		ret = btrfs_readpage(NULL, page);
		if (ret)
			return ERR_PTR(ret);
		lock_page(page);
		if (!PageUptodate(page)) {
			unlock_page(page);
			put_page(page);
			return ERR_PTR(-EIO);
		}
		if (page->mapping != inode->i_mapping) {
			unlock_page(page);
			put_page(page);
			return ERR_PTR(-EAGAIN);
		}
	}

	return page;
}