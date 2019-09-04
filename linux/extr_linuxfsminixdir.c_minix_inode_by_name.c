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
struct page {struct address_space* mapping; } ;
struct minix_sb_info {scalar_t__ s_version; } ;
struct minix_dir_entry {int /*<<< orphan*/  inode; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  inode; } ;
typedef  TYPE_1__ minix3_dirent ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ MINIX_V3 ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 struct minix_dir_entry* minix_find_entry (struct dentry*,struct page**) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 

ino_t minix_inode_by_name(struct dentry *dentry)
{
	struct page *page;
	struct minix_dir_entry *de = minix_find_entry(dentry, &page);
	ino_t res = 0;

	if (de) {
		struct address_space *mapping = page->mapping;
		struct inode *inode = mapping->host;
		struct minix_sb_info *sbi = minix_sb(inode->i_sb);

		if (sbi->s_version == MINIX_V3)
			res = ((minix3_dirent *) de)->inode;
		else
			res = de->inode;
		dir_put_page(page);
	}
	return res;
}