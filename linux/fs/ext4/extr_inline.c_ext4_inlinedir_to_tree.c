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
struct inode {unsigned int i_ino; int /*<<< orphan*/  i_sb; } ;
struct fscrypt_str {int len; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct ext4_dir_entry_2 {scalar_t__ inode; int name_len; int /*<<< orphan*/  name; void* rec_len; } ;
struct dx_hash_info {scalar_t__ hash; scalar_t__ minor_hash; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_DIR_REC_LEN (int) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int EXT4_INLINE_DOTDOT_OFFSET ; 
 int EXT4_INLINE_DOTDOT_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_check_dir_entry (struct inode*,struct file*,struct ext4_dir_entry_2*,int /*<<< orphan*/ ,void*,int,int) ; 
 int ext4_get_inline_size (struct inode*) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_htree_store_dirent (struct file*,scalar_t__,scalar_t__,struct ext4_dir_entry_2*,struct fscrypt_str*) ; 
 int ext4_read_inline_data (struct inode*,void*,int,struct ext4_iloc*) ; 
 scalar_t__ ext4_rec_len_from_disk (void*,int) ; 
 void* ext4_rec_len_to_disk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_set_de_type (int /*<<< orphan*/ ,struct ext4_dir_entry_2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4fs_dirhash (struct inode*,int /*<<< orphan*/ ,int,struct dx_hash_info*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_inlinedir_to_tree(struct file *dir_file,
			   struct inode *dir, ext4_lblk_t block,
			   struct dx_hash_info *hinfo,
			   __u32 start_hash, __u32 start_minor_hash,
			   int *has_inline_data)
{
	int err = 0, count = 0;
	unsigned int parent_ino;
	int pos;
	struct ext4_dir_entry_2 *de;
	struct inode *inode = file_inode(dir_file);
	int ret, inline_size = 0;
	struct ext4_iloc iloc;
	void *dir_buf = NULL;
	struct ext4_dir_entry_2 fake;
	struct fscrypt_str tmp_str;

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret)
		return ret;

	down_read(&EXT4_I(inode)->xattr_sem);
	if (!ext4_has_inline_data(inode)) {
		up_read(&EXT4_I(inode)->xattr_sem);
		*has_inline_data = 0;
		goto out;
	}

	inline_size = ext4_get_inline_size(inode);
	dir_buf = kmalloc(inline_size, GFP_NOFS);
	if (!dir_buf) {
		ret = -ENOMEM;
		up_read(&EXT4_I(inode)->xattr_sem);
		goto out;
	}

	ret = ext4_read_inline_data(inode, dir_buf, inline_size, &iloc);
	up_read(&EXT4_I(inode)->xattr_sem);
	if (ret < 0)
		goto out;

	pos = 0;
	parent_ino = le32_to_cpu(((struct ext4_dir_entry_2 *)dir_buf)->inode);
	while (pos < inline_size) {
		/*
		 * As inlined dir doesn't store any information about '.' and
		 * only the inode number of '..' is stored, we have to handle
		 * them differently.
		 */
		if (pos == 0) {
			fake.inode = cpu_to_le32(inode->i_ino);
			fake.name_len = 1;
			strcpy(fake.name, ".");
			fake.rec_len = ext4_rec_len_to_disk(
						EXT4_DIR_REC_LEN(fake.name_len),
						inline_size);
			ext4_set_de_type(inode->i_sb, &fake, S_IFDIR);
			de = &fake;
			pos = EXT4_INLINE_DOTDOT_OFFSET;
		} else if (pos == EXT4_INLINE_DOTDOT_OFFSET) {
			fake.inode = cpu_to_le32(parent_ino);
			fake.name_len = 2;
			strcpy(fake.name, "..");
			fake.rec_len = ext4_rec_len_to_disk(
						EXT4_DIR_REC_LEN(fake.name_len),
						inline_size);
			ext4_set_de_type(inode->i_sb, &fake, S_IFDIR);
			de = &fake;
			pos = EXT4_INLINE_DOTDOT_SIZE;
		} else {
			de = (struct ext4_dir_entry_2 *)(dir_buf + pos);
			pos += ext4_rec_len_from_disk(de->rec_len, inline_size);
			if (ext4_check_dir_entry(inode, dir_file, de,
					 iloc.bh, dir_buf,
					 inline_size, pos)) {
				ret = count;
				goto out;
			}
		}

		ext4fs_dirhash(dir, de->name, de->name_len, hinfo);
		if ((hinfo->hash < start_hash) ||
		    ((hinfo->hash == start_hash) &&
		     (hinfo->minor_hash < start_minor_hash)))
			continue;
		if (de->inode == 0)
			continue;
		tmp_str.name = de->name;
		tmp_str.len = de->name_len;
		err = ext4_htree_store_dirent(dir_file, hinfo->hash,
					      hinfo->minor_hash, de, &tmp_str);
		if (err) {
			ret = err;
			goto out;
		}
		count++;
	}
	ret = count;
out:
	kfree(dir_buf);
	brelse(iloc.bh);
	return ret;
}