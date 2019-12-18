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
struct inode {scalar_t__ i_sb; size_t i_size; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {scalar_t__ mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  size_t loff_t ;
struct TYPE_4__ {int /*<<< orphan*/ * i_gc_rwsem; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int EXDEV ; 
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 size_t F2FS_BLKSIZE_BITS ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  IS_ALIGNED (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 size_t WRITE ; 
 int __exchange_data_block (struct inode*,struct inode*,size_t,size_t,size_t,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,size_t) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_readonly (scalar_t__) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_trylock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_move_file_range(struct file *file_in, loff_t pos_in,
			struct file *file_out, loff_t pos_out, size_t len)
{
	struct inode *src = file_inode(file_in);
	struct inode *dst = file_inode(file_out);
	struct f2fs_sb_info *sbi = F2FS_I_SB(src);
	size_t olen = len, dst_max_i_size = 0;
	size_t dst_osize;
	int ret;

	if (file_in->f_path.mnt != file_out->f_path.mnt ||
				src->i_sb != dst->i_sb)
		return -EXDEV;

	if (unlikely(f2fs_readonly(src->i_sb)))
		return -EROFS;

	if (!S_ISREG(src->i_mode) || !S_ISREG(dst->i_mode))
		return -EINVAL;

	if (IS_ENCRYPTED(src) || IS_ENCRYPTED(dst))
		return -EOPNOTSUPP;

	if (src == dst) {
		if (pos_in == pos_out)
			return 0;
		if (pos_out > pos_in && pos_out < pos_in + len)
			return -EINVAL;
	}

	inode_lock(src);
	if (src != dst) {
		ret = -EBUSY;
		if (!inode_trylock(dst))
			goto out;
	}

	ret = -EINVAL;
	if (pos_in + len > src->i_size || pos_in + len < pos_in)
		goto out_unlock;
	if (len == 0)
		olen = len = src->i_size - pos_in;
	if (pos_in + len == src->i_size)
		len = ALIGN(src->i_size, F2FS_BLKSIZE) - pos_in;
	if (len == 0) {
		ret = 0;
		goto out_unlock;
	}

	dst_osize = dst->i_size;
	if (pos_out + olen > dst->i_size)
		dst_max_i_size = pos_out + olen;

	/* verify the end result is block aligned */
	if (!IS_ALIGNED(pos_in, F2FS_BLKSIZE) ||
			!IS_ALIGNED(pos_in + len, F2FS_BLKSIZE) ||
			!IS_ALIGNED(pos_out, F2FS_BLKSIZE))
		goto out_unlock;

	ret = f2fs_convert_inline_inode(src);
	if (ret)
		goto out_unlock;

	ret = f2fs_convert_inline_inode(dst);
	if (ret)
		goto out_unlock;

	/* write out all dirty pages from offset */
	ret = filemap_write_and_wait_range(src->i_mapping,
					pos_in, pos_in + len);
	if (ret)
		goto out_unlock;

	ret = filemap_write_and_wait_range(dst->i_mapping,
					pos_out, pos_out + len);
	if (ret)
		goto out_unlock;

	f2fs_balance_fs(sbi, true);

	down_write(&F2FS_I(src)->i_gc_rwsem[WRITE]);
	if (src != dst) {
		ret = -EBUSY;
		if (!down_write_trylock(&F2FS_I(dst)->i_gc_rwsem[WRITE]))
			goto out_src;
	}

	f2fs_lock_op(sbi);
	ret = __exchange_data_block(src, dst, pos_in >> F2FS_BLKSIZE_BITS,
				pos_out >> F2FS_BLKSIZE_BITS,
				len >> F2FS_BLKSIZE_BITS, false);

	if (!ret) {
		if (dst_max_i_size)
			f2fs_i_size_write(dst, dst_max_i_size);
		else if (dst_osize != dst->i_size)
			f2fs_i_size_write(dst, dst_osize);
	}
	f2fs_unlock_op(sbi);

	if (src != dst)
		up_write(&F2FS_I(dst)->i_gc_rwsem[WRITE]);
out_src:
	up_write(&F2FS_I(src)->i_gc_rwsem[WRITE]);
out_unlock:
	if (src != dst)
		inode_unlock(dst);
out:
	inode_unlock(src);
	return ret;
}