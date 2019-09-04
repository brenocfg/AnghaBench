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
struct super_block {int dummy; } ;
struct inode {int i_ino; struct super_block* i_sb; } ;
struct file {int /*<<< orphan*/  f_version; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct ext4_dir_entry_2 {char* name; int name_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  file_type; int /*<<< orphan*/  inode; } ;
struct dir_context {unsigned int pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int ENOMEM ; 
 int EXT4_DIR_REC_LEN (int) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int EXT4_INLINE_DOTDOT_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_check_dir_entry (struct inode*,struct file*,struct ext4_dir_entry_2*,int /*<<< orphan*/ ,void*,int,void*) ; 
 int ext4_get_inline_size (struct inode*) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_read_inline_data (struct inode*,void*,int,struct ext4_iloc*) ; 
 int ext4_rec_len_from_disk (int /*<<< orphan*/ ,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  get_dtype (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_eq_iversion (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_read_inline_dir(struct file *file,
			 struct dir_context *ctx,
			 int *has_inline_data)
{
	unsigned int offset, parent_ino;
	int i;
	struct ext4_dir_entry_2 *de;
	struct super_block *sb;
	struct inode *inode = file_inode(file);
	int ret, inline_size = 0;
	struct ext4_iloc iloc;
	void *dir_buf = NULL;
	int dotdot_offset, dotdot_size, extra_offset, extra_size;

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

	ret = 0;
	sb = inode->i_sb;
	parent_ino = le32_to_cpu(((struct ext4_dir_entry_2 *)dir_buf)->inode);
	offset = ctx->pos;

	/*
	 * dotdot_offset and dotdot_size is the real offset and
	 * size for ".." and "." if the dir is block based while
	 * the real size for them are only EXT4_INLINE_DOTDOT_SIZE.
	 * So we will use extra_offset and extra_size to indicate them
	 * during the inline dir iteration.
	 */
	dotdot_offset = EXT4_DIR_REC_LEN(1);
	dotdot_size = dotdot_offset + EXT4_DIR_REC_LEN(2);
	extra_offset = dotdot_size - EXT4_INLINE_DOTDOT_SIZE;
	extra_size = extra_offset + inline_size;

	/*
	 * If the version has changed since the last call to
	 * readdir(2), then we might be pointing to an invalid
	 * dirent right now.  Scan from the start of the inline
	 * dir to make sure.
	 */
	if (!inode_eq_iversion(inode, file->f_version)) {
		for (i = 0; i < extra_size && i < offset;) {
			/*
			 * "." is with offset 0 and
			 * ".." is dotdot_offset.
			 */
			if (!i) {
				i = dotdot_offset;
				continue;
			} else if (i == dotdot_offset) {
				i = dotdot_size;
				continue;
			}
			/* for other entry, the real offset in
			 * the buf has to be tuned accordingly.
			 */
			de = (struct ext4_dir_entry_2 *)
				(dir_buf + i - extra_offset);
			/* It's too expensive to do a full
			 * dirent test each time round this
			 * loop, but we do have to test at
			 * least that it is non-zero.  A
			 * failure will be detected in the
			 * dirent test below. */
			if (ext4_rec_len_from_disk(de->rec_len, extra_size)
				< EXT4_DIR_REC_LEN(1))
				break;
			i += ext4_rec_len_from_disk(de->rec_len,
						    extra_size);
		}
		offset = i;
		ctx->pos = offset;
		file->f_version = inode_query_iversion(inode);
	}

	while (ctx->pos < extra_size) {
		if (ctx->pos == 0) {
			if (!dir_emit(ctx, ".", 1, inode->i_ino, DT_DIR))
				goto out;
			ctx->pos = dotdot_offset;
			continue;
		}

		if (ctx->pos == dotdot_offset) {
			if (!dir_emit(ctx, "..", 2, parent_ino, DT_DIR))
				goto out;
			ctx->pos = dotdot_size;
			continue;
		}

		de = (struct ext4_dir_entry_2 *)
			(dir_buf + ctx->pos - extra_offset);
		if (ext4_check_dir_entry(inode, file, de, iloc.bh, dir_buf,
					 extra_size, ctx->pos))
			goto out;
		if (le32_to_cpu(de->inode)) {
			if (!dir_emit(ctx, de->name, de->name_len,
				      le32_to_cpu(de->inode),
				      get_dtype(sb, de->file_type)))
				goto out;
		}
		ctx->pos += ext4_rec_len_from_disk(de->rec_len, extra_size);
	}
out:
	kfree(dir_buf);
	brelse(iloc.bh);
	return ret;
}