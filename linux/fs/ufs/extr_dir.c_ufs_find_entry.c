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
struct ufs_inode_info {unsigned long i_dir_start_lookup; } ;
struct ufs_dir_entry {int dummy; } ;
struct super_block {int dummy; } ;
struct qstr {unsigned char* name; int len; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 unsigned int UFS_DIR_REC_LEN (int) ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 int UFS_MAXNAMLEN ; 
 unsigned long dir_pages (struct inode*) ; 
 char* page_address (struct page*) ; 
 struct page* ufs_get_page (struct inode*,unsigned long) ; 
 unsigned int ufs_last_byte (struct inode*,unsigned long) ; 
 scalar_t__ ufs_match (struct super_block*,int,unsigned char const*,struct ufs_dir_entry*) ; 
 struct ufs_dir_entry* ufs_next_entry (struct super_block*,struct ufs_dir_entry*) ; 
 int /*<<< orphan*/  ufs_put_page (struct page*) ; 

struct ufs_dir_entry *ufs_find_entry(struct inode *dir, const struct qstr *qstr,
				     struct page **res_page)
{
	struct super_block *sb = dir->i_sb;
	const unsigned char *name = qstr->name;
	int namelen = qstr->len;
	unsigned reclen = UFS_DIR_REC_LEN(namelen);
	unsigned long start, n;
	unsigned long npages = dir_pages(dir);
	struct page *page = NULL;
	struct ufs_inode_info *ui = UFS_I(dir);
	struct ufs_dir_entry *de;

	UFSD("ENTER, dir_ino %lu, name %s, namlen %u\n", dir->i_ino, name, namelen);

	if (npages == 0 || namelen > UFS_MAXNAMLEN)
		goto out;

	/* OFFSET_CACHE */
	*res_page = NULL;

	start = ui->i_dir_start_lookup;

	if (start >= npages)
		start = 0;
	n = start;
	do {
		char *kaddr;
		page = ufs_get_page(dir, n);
		if (!IS_ERR(page)) {
			kaddr = page_address(page);
			de = (struct ufs_dir_entry *) kaddr;
			kaddr += ufs_last_byte(dir, n) - reclen;
			while ((char *) de <= kaddr) {
				if (ufs_match(sb, namelen, name, de))
					goto found;
				de = ufs_next_entry(sb, de);
			}
			ufs_put_page(page);
		}
		if (++n >= npages)
			n = 0;
	} while (n != start);
out:
	return NULL;

found:
	*res_page = page;
	ui->i_dir_start_lookup = n;
	return de;
}