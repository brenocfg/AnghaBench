#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct minix_sb_info {scalar_t__ s_version; int /*<<< orphan*/  s_dirsize; } ;
struct minix_dir_entry {int /*<<< orphan*/  inode; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;
typedef  TYPE_2__ minix3_dirent ;
typedef  int loff_t ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ MINIX_V3 ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dir_commit_chunk (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int minix_prepare_chunk (struct page*,int,int /*<<< orphan*/ ) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void minix_set_link(struct minix_dir_entry *de, struct page *page,
	struct inode *inode)
{
	struct inode *dir = page->mapping->host;
	struct minix_sb_info *sbi = minix_sb(dir->i_sb);
	loff_t pos = page_offset(page) +
			(char *)de-(char*)page_address(page);
	int err;

	lock_page(page);

	err = minix_prepare_chunk(page, pos, sbi->s_dirsize);
	if (err == 0) {
		if (sbi->s_version == MINIX_V3)
			((minix3_dirent *) de)->inode = inode->i_ino;
		else
			de->inode = inode->i_ino;
		err = dir_commit_chunk(page, pos, sbi->s_dirsize);
	} else {
		unlock_page(page);
	}
	dir_put_page(page);
	dir->i_mtime = dir->i_ctime = current_time(dir);
	mark_inode_dirty(dir);
}