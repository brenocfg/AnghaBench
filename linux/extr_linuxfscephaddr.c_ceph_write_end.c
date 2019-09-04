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
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CAPS_AUTHONLY ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  ceph_check_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_inode (struct inode*) ; 
 int ceph_inode_set_size (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  dout (char*,struct file*,struct inode*,struct page*,int,int,int) ; 
 struct inode* file_inode (struct file*) ; 
 unsigned int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ceph_write_end(struct file *file, struct address_space *mapping,
			  loff_t pos, unsigned len, unsigned copied,
			  struct page *page, void *fsdata)
{
	struct inode *inode = file_inode(file);
	bool check_cap = false;

	dout("write_end file %p inode %p page %p %d~%d (%d)\n", file,
	     inode, page, (int)pos, (int)copied, (int)len);

	/* zero the stale part of the page if we did a short copy */
	if (!PageUptodate(page)) {
		if (copied < len) {
			copied = 0;
			goto out;
		}
		SetPageUptodate(page);
	}

	/* did file size increase? */
	if (pos+copied > i_size_read(inode))
		check_cap = ceph_inode_set_size(inode, pos+copied);

	set_page_dirty(page);

out:
	unlock_page(page);
	put_page(page);

	if (check_cap)
		ceph_check_caps(ceph_inode(inode), CHECK_CAPS_AUTHONLY, NULL);

	return copied;
}