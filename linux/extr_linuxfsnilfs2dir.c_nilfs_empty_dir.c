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
struct nilfs_dir_entry {scalar_t__ rec_len; scalar_t__ inode; char* name; int name_len; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ NILFS_DIR_REC_LEN (int) ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  nilfs_error (int /*<<< orphan*/ ,char*,char*,struct nilfs_dir_entry*) ; 
 struct page* nilfs_get_page (struct inode*,unsigned long) ; 
 scalar_t__ nilfs_last_byte (struct inode*,unsigned long) ; 
 struct nilfs_dir_entry* nilfs_next_entry (struct nilfs_dir_entry*) ; 
 int /*<<< orphan*/  nilfs_put_page (struct page*) ; 
 char* page_address (struct page*) ; 

int nilfs_empty_dir(struct inode *inode)
{
	struct page *page = NULL;
	unsigned long i, npages = dir_pages(inode);

	for (i = 0; i < npages; i++) {
		char *kaddr;
		struct nilfs_dir_entry *de;

		page = nilfs_get_page(inode, i);
		if (IS_ERR(page))
			continue;

		kaddr = page_address(page);
		de = (struct nilfs_dir_entry *)kaddr;
		kaddr += nilfs_last_byte(inode, i) - NILFS_DIR_REC_LEN(1);

		while ((char *)de <= kaddr) {
			if (de->rec_len == 0) {
				nilfs_error(inode->i_sb,
					    "zero-length directory entry (kaddr=%p, de=%p)",
					    kaddr, de);
				goto not_empty;
			}
			if (de->inode != 0) {
				/* check for . and .. */
				if (de->name[0] != '.')
					goto not_empty;
				if (de->name_len > 2)
					goto not_empty;
				if (de->name_len < 2) {
					if (de->inode !=
					    cpu_to_le64(inode->i_ino))
						goto not_empty;
				} else if (de->name[1] != '.')
					goto not_empty;
			}
			de = nilfs_next_entry(de);
		}
		nilfs_put_page(page);
	}
	return 1;

not_empty:
	nilfs_put_page(page);
	return 0;
}