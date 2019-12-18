#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int fuse_do_readpage (struct file*,struct page*) ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int fuse_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int err;

	err = -EIO;
	if (is_bad_inode(inode))
		goto out;

	err = fuse_do_readpage(file, page);
	fuse_invalidate_atime(inode);
 out:
	unlock_page(page);
	return err;
}