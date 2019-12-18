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
struct page {struct address_space* mapping; } ;
struct nilfs_dir_entry {int /*<<< orphan*/  inode; int /*<<< orphan*/  rec_len; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_commit_chunk (struct page*,struct address_space*,unsigned int,unsigned int) ; 
 int nilfs_prepare_chunk (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nilfs_put_page (struct page*) ; 
 unsigned int nilfs_rec_len_from_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_set_de_type (struct nilfs_dir_entry*,struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 

void nilfs_set_link(struct inode *dir, struct nilfs_dir_entry *de,
		    struct page *page, struct inode *inode)
{
	unsigned int from = (char *)de - (char *)page_address(page);
	unsigned int to = from + nilfs_rec_len_from_disk(de->rec_len);
	struct address_space *mapping = page->mapping;
	int err;

	lock_page(page);
	err = nilfs_prepare_chunk(page, from, to);
	BUG_ON(err);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);
	nilfs_commit_chunk(page, mapping, from, to);
	nilfs_put_page(page);
	dir->i_mtime = dir->i_ctime = current_time(dir);
}