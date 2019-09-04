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
struct sysv_dir_entry {scalar_t__ inode; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
typedef  int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SYSV_DIRSIZE ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dir_commit_chunk (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int sysv_prepare_chunk (struct page*,int,int /*<<< orphan*/ ) ; 

int sysv_delete_entry(struct sysv_dir_entry *de, struct page *page)
{
	struct inode *inode = page->mapping->host;
	char *kaddr = (char*)page_address(page);
	loff_t pos = page_offset(page) + (char *)de - kaddr;
	int err;

	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_DIRSIZE);
	BUG_ON(err);
	de->inode = 0;
	err = dir_commit_chunk(page, pos, SYSV_DIRSIZE);
	dir_put_page(page);
	inode->i_ctime = inode->i_mtime = current_time(inode);
	mark_inode_dirty(inode);
	return err;
}