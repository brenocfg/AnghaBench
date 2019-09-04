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
struct page {int /*<<< orphan*/  mapping; } ;
struct nilfs_dir_entry {scalar_t__ rec_len; int name_len; scalar_t__ inode; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {unsigned char* name; int len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct page*) ; 
 void* NILFS_DIR_REC_LEN (int) ; 
 unsigned int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 unsigned int nilfs_chunk_size (struct inode*) ; 
 int /*<<< orphan*/  nilfs_commit_chunk (struct page*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nilfs_error (int /*<<< orphan*/ ,char*) ; 
 struct page* nilfs_get_page (struct inode*,unsigned long) ; 
 int nilfs_last_byte (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  nilfs_mark_inode_dirty (struct inode*) ; 
 scalar_t__ nilfs_match (int,unsigned char const*,struct nilfs_dir_entry*) ; 
 int nilfs_prepare_chunk (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nilfs_put_page (struct page*) ; 
 unsigned short nilfs_rec_len_from_disk (scalar_t__) ; 
 void* nilfs_rec_len_to_disk (unsigned short) ; 
 int /*<<< orphan*/  nilfs_set_de_type (struct nilfs_dir_entry*,struct inode*) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nilfs_add_link(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = d_inode(dentry->d_parent);
	const unsigned char *name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	unsigned int chunk_size = nilfs_chunk_size(dir);
	unsigned int reclen = NILFS_DIR_REC_LEN(namelen);
	unsigned short rec_len, name_len;
	struct page *page = NULL;
	struct nilfs_dir_entry *de;
	unsigned long npages = dir_pages(dir);
	unsigned long n;
	char *kaddr;
	unsigned int from, to;
	int err;

	/*
	 * We take care of directory expansion in the same loop.
	 * This code plays outside i_size, so it locks the page
	 * to protect that region.
	 */
	for (n = 0; n <= npages; n++) {
		char *dir_end;

		page = nilfs_get_page(dir, n);
		err = PTR_ERR(page);
		if (IS_ERR(page))
			goto out;
		lock_page(page);
		kaddr = page_address(page);
		dir_end = kaddr + nilfs_last_byte(dir, n);
		de = (struct nilfs_dir_entry *)kaddr;
		kaddr += PAGE_SIZE - reclen;
		while ((char *)de <= kaddr) {
			if ((char *)de == dir_end) {
				/* We hit i_size */
				name_len = 0;
				rec_len = chunk_size;
				de->rec_len = nilfs_rec_len_to_disk(chunk_size);
				de->inode = 0;
				goto got_it;
			}
			if (de->rec_len == 0) {
				nilfs_error(dir->i_sb,
					    "zero-length directory entry");
				err = -EIO;
				goto out_unlock;
			}
			err = -EEXIST;
			if (nilfs_match(namelen, name, de))
				goto out_unlock;
			name_len = NILFS_DIR_REC_LEN(de->name_len);
			rec_len = nilfs_rec_len_from_disk(de->rec_len);
			if (!de->inode && rec_len >= reclen)
				goto got_it;
			if (rec_len >= name_len + reclen)
				goto got_it;
			de = (struct nilfs_dir_entry *)((char *)de + rec_len);
		}
		unlock_page(page);
		nilfs_put_page(page);
	}
	BUG();
	return -EINVAL;

got_it:
	from = (char *)de - (char *)page_address(page);
	to = from + rec_len;
	err = nilfs_prepare_chunk(page, from, to);
	if (err)
		goto out_unlock;
	if (de->inode) {
		struct nilfs_dir_entry *de1;

		de1 = (struct nilfs_dir_entry *)((char *)de + name_len);
		de1->rec_len = nilfs_rec_len_to_disk(rec_len - name_len);
		de->rec_len = nilfs_rec_len_to_disk(name_len);
		de = de1;
	}
	de->name_len = namelen;
	memcpy(de->name, name, namelen);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);
	nilfs_commit_chunk(page, page->mapping, from, to);
	dir->i_mtime = dir->i_ctime = current_time(dir);
	nilfs_mark_inode_dirty(dir);
	/* OFFSET_CACHE */
out_put:
	nilfs_put_page(page);
out:
	return err;
out_unlock:
	unlock_page(page);
	goto out_put;
}