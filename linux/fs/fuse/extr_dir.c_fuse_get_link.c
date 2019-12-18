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
struct inode {int dummy; } ;
struct fuse_conn {scalar_t__ cache_symlinks; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int EIO ; 
 int ENOMEM ; 
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int fuse_readlink_page (struct inode*,struct page*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 char const* page_address (struct page*) ; 
 char const* page_get_link (struct dentry*,struct inode*,struct delayed_call*) ; 
 int /*<<< orphan*/  page_put_link ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static const char *fuse_get_link(struct dentry *dentry, struct inode *inode,
				 struct delayed_call *callback)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct page *page;
	int err;

	err = -EIO;
	if (is_bad_inode(inode))
		goto out_err;

	if (fc->cache_symlinks)
		return page_get_link(dentry, inode, callback);

	err = -ECHILD;
	if (!dentry)
		goto out_err;

	page = alloc_page(GFP_KERNEL);
	err = -ENOMEM;
	if (!page)
		goto out_err;

	err = fuse_readlink_page(inode, page);
	if (err) {
		__free_page(page);
		goto out_err;
	}

	set_delayed_call(callback, page_put_link, page);

	return page_address(page);

out_err:
	return ERR_PTR(err);
}