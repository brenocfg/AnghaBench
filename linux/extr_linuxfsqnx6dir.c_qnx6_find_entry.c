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
struct super_block {int dummy; } ;
struct qnx6_long_dir_entry {int dummy; } ;
struct qnx6_inode_info {unsigned long i_dir_start_lookup; } ;
struct qnx6_dir_entry {int de_size; } ;
struct page {int dummy; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 struct qnx6_inode_info* QNX6_I (struct inode*) ; 
 int QNX6_SHORT_NAME_MAX ; 
 unsigned long dir_pages (struct inode*) ; 
 int last_entry (struct inode*,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct page* qnx6_get_page (struct inode*,unsigned long) ; 
 unsigned int qnx6_long_match (int,char const*,struct qnx6_long_dir_entry*,struct inode*) ; 
 unsigned int qnx6_match (struct super_block*,int,char const*,struct qnx6_dir_entry*) ; 
 int /*<<< orphan*/  qnx6_put_page (struct page*) ; 

unsigned qnx6_find_entry(int len, struct inode *dir, const char *name,
			 struct page **res_page)
{
	struct super_block *s = dir->i_sb;
	struct qnx6_inode_info *ei = QNX6_I(dir);
	struct page *page = NULL;
	unsigned long start, n;
	unsigned long npages = dir_pages(dir);
	unsigned ino;
	struct qnx6_dir_entry *de;
	struct qnx6_long_dir_entry *lde;

	*res_page = NULL;

	if (npages == 0)
		return 0;
	start = ei->i_dir_start_lookup;
	if (start >= npages)
		start = 0;
	n = start;

	do {
		page = qnx6_get_page(dir, n);
		if (!IS_ERR(page)) {
			int limit = last_entry(dir, n);
			int i;

			de = (struct qnx6_dir_entry *)page_address(page);
			for (i = 0; i < limit; i++, de++) {
				if (len <= QNX6_SHORT_NAME_MAX) {
					/* short filename */
					if (len != de->de_size)
						continue;
					ino = qnx6_match(s, len, name, de);
					if (ino)
						goto found;
				} else if (de->de_size == 0xff) {
					/* deal with long filename */
					lde = (struct qnx6_long_dir_entry *)de;
					ino = qnx6_long_match(len,
								name, lde, dir);
					if (ino)
						goto found;
				} else
					pr_err("undefined filename size in inode.\n");
			}
			qnx6_put_page(page);
		}

		if (++n >= npages)
			n = 0;
	} while (n != start);
	return 0;

found:
	*res_page = page;
	ei->i_dir_start_lookup = n;
	return ino;
}