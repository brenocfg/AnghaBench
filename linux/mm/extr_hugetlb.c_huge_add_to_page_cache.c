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
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_blocks; } ;
struct hstate {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int add_to_page_cache (struct page*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blocks_per_huge_page (struct hstate*) ; 
 struct hstate* hstate_inode (struct inode*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int huge_add_to_page_cache(struct page *page, struct address_space *mapping,
			   pgoff_t idx)
{
	struct inode *inode = mapping->host;
	struct hstate *h = hstate_inode(inode);
	int err = add_to_page_cache(page, mapping, idx, GFP_KERNEL);

	if (err)
		return err;
	ClearPagePrivate(page);

	/*
	 * set page dirty so that it will not be removed from cache/file
	 * by non-hugetlbfs specific code paths.
	 */
	set_page_dirty(page);

	spin_lock(&inode->i_lock);
	inode->i_blocks += blocks_per_huge_page(h);
	spin_unlock(&inode->i_lock);
	return 0;
}