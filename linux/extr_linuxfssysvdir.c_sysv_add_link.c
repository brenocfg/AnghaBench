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
struct sysv_dir_entry {scalar_t__ inode; int /*<<< orphan*/  name; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_NAMELEN ; 
 int /*<<< orphan*/  SYSV_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_fs16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int dir_commit_chunk (struct page*,int,int) ; 
 struct page* dir_get_page (struct inode*,unsigned long) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ namecompare (int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int sysv_prepare_chunk (struct page*,int,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int sysv_add_link(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = d_inode(dentry->d_parent);
	const char * name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	struct page *page = NULL;
	struct sysv_dir_entry * de;
	unsigned long npages = dir_pages(dir);
	unsigned long n;
	char *kaddr;
	loff_t pos;
	int err;

	/* We take care of directory expansion in the same loop */
	for (n = 0; n <= npages; n++) {
		page = dir_get_page(dir, n);
		err = PTR_ERR(page);
		if (IS_ERR(page))
			goto out;
		kaddr = (char*)page_address(page);
		de = (struct sysv_dir_entry *)kaddr;
		kaddr += PAGE_SIZE - SYSV_DIRSIZE;
		while ((char *)de <= kaddr) {
			if (!de->inode)
				goto got_it;
			err = -EEXIST;
			if (namecompare(namelen, SYSV_NAMELEN, name, de->name)) 
				goto out_page;
			de++;
		}
		dir_put_page(page);
	}
	BUG();
	return -EINVAL;

got_it:
	pos = page_offset(page) +
			(char*)de - (char*)page_address(page);
	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_DIRSIZE);
	if (err)
		goto out_unlock;
	memcpy (de->name, name, namelen);
	memset (de->name + namelen, 0, SYSV_DIRSIZE - namelen - 2);
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	err = dir_commit_chunk(page, pos, SYSV_DIRSIZE);
	dir->i_mtime = dir->i_ctime = current_time(dir);
	mark_inode_dirty(dir);
out_page:
	dir_put_page(page);
out:
	return err;
out_unlock:
	unlock_page(page);
	goto out_page;
}