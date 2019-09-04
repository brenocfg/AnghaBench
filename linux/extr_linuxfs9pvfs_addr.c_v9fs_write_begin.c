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
struct v9fs_inode {int /*<<< orphan*/  writeback_fid; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct file*,struct address_space*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int v9fs_fid_readpage (int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static int v9fs_write_begin(struct file *filp, struct address_space *mapping,
			    loff_t pos, unsigned len, unsigned flags,
			    struct page **pagep, void **fsdata)
{
	int retval = 0;
	struct page *page;
	struct v9fs_inode *v9inode;
	pgoff_t index = pos >> PAGE_SHIFT;
	struct inode *inode = mapping->host;


	p9_debug(P9_DEBUG_VFS, "filp %p, mapping %p\n", filp, mapping);

	v9inode = V9FS_I(inode);
start:
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page) {
		retval = -ENOMEM;
		goto out;
	}
	BUG_ON(!v9inode->writeback_fid);
	if (PageUptodate(page))
		goto out;

	if (len == PAGE_SIZE)
		goto out;

	retval = v9fs_fid_readpage(v9inode->writeback_fid, page);
	put_page(page);
	if (!retval)
		goto start;
out:
	*pagep = page;
	return retval;
}