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
struct sysv_dir_entry {int /*<<< orphan*/  inode; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
typedef  int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fs16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dir_commit_chunk (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int sysv_prepare_chunk (struct page*,int,int /*<<< orphan*/ ) ; 

void sysv_set_link(struct sysv_dir_entry *de, struct page *page,
	struct inode *inode)
{
	struct inode *dir = page->mapping->host;
	loff_t pos = page_offset(page) +
			(char *)de-(char*)page_address(page);
	int err;

	lock_page(page);
	err = sysv_prepare_chunk(page, pos, SYSV_DIRSIZE);
	BUG_ON(err);
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	err = dir_commit_chunk(page, pos, SYSV_DIRSIZE);
	dir_put_page(page);
	dir->i_mtime = dir->i_ctime = current_time(dir);
	mark_inode_dirty(dir);
}