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
struct inode {int /*<<< orphan*/  i_size; struct address_space* i_mapping; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int __GFP_HIGHMEM ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  nd_terminate_link (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  page_put_link ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,struct page*) ; 

const char *page_get_link(struct dentry *dentry, struct inode *inode,
			  struct delayed_call *callback)
{
	char *kaddr;
	struct page *page;
	struct address_space *mapping = inode->i_mapping;

	if (!dentry) {
		page = find_get_page(mapping, 0);
		if (!page)
			return ERR_PTR(-ECHILD);
		if (!PageUptodate(page)) {
			put_page(page);
			return ERR_PTR(-ECHILD);
		}
	} else {
		page = read_mapping_page(mapping, 0, NULL);
		if (IS_ERR(page))
			return (char*)page;
	}
	set_delayed_call(callback, page_put_link, page);
	BUG_ON(mapping_gfp_mask(mapping) & __GFP_HIGHMEM);
	kaddr = page_address(page);
	nd_terminate_link(kaddr, inode->i_size, PAGE_SIZE - 1);
	return kaddr;
}