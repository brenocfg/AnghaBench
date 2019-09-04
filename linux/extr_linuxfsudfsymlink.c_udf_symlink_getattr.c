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
typedef  int /*<<< orphan*/  u32 ;
struct path {struct dentry* dentry; } ;
struct page {int dummy; } ;
struct kstat {int /*<<< orphan*/  size; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_symlink_getattr(const struct path *path, struct kstat *stat,
				u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	struct inode *inode = d_backing_inode(dentry);
	struct page *page;

	generic_fillattr(inode, stat);
	page = read_mapping_page(inode->i_mapping, 0, NULL);
	if (IS_ERR(page))
		return PTR_ERR(page);
	/*
	 * UDF uses non-trivial encoding of symlinks so i_size does not match
	 * number of characters reported by readlink(2) which apparently some
	 * applications expect. Also POSIX says that "The value returned in the
	 * st_size field shall be the length of the contents of the symbolic
	 * link, and shall not count a trailing null if one is present." So
	 * let's report the length of string returned by readlink(2) for
	 * st_size.
	 */
	stat->size = strlen(page_address(page));
	put_page(page);

	return 0;
}