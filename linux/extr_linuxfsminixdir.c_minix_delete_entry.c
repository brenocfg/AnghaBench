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
struct minix_sb_info {unsigned int s_dirsize; scalar_t__ s_version; } ;
struct minix_dir_entry {scalar_t__ inode; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {scalar_t__ inode; } ;
typedef  TYPE_2__ minix3_dirent ;
typedef  int loff_t ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ MINIX_V3 ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dir_commit_chunk (struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int minix_prepare_chunk (struct page*,int,unsigned int) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 
 char* page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int minix_delete_entry(struct minix_dir_entry *de, struct page *page)
{
	struct inode *inode = page->mapping->host;
	char *kaddr = page_address(page);
	loff_t pos = page_offset(page) + (char*)de - kaddr;
	struct minix_sb_info *sbi = minix_sb(inode->i_sb);
	unsigned len = sbi->s_dirsize;
	int err;

	lock_page(page);
	err = minix_prepare_chunk(page, pos, len);
	if (err == 0) {
		if (sbi->s_version == MINIX_V3)
			((minix3_dirent *) de)->inode = 0;
		else
			de->inode = 0;
		err = dir_commit_chunk(page, pos, len);
	} else {
		unlock_page(page);
	}
	dir_put_page(page);
	inode->i_ctime = inode->i_mtime = current_time(inode);
	mark_inode_dirty(inode);
	return err;
}