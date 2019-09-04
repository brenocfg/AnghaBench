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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; int f_flags; TYPE_1__* f_op; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* clone_file_range ) (struct file*,scalar_t__,struct file*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EISDIR ; 
 int EOPNOTSUPP ; 
 int EXDEV ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int O_APPEND ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int clone_verify_area (struct file*,scalar_t__,scalar_t__,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fsnotify_access (struct file*) ; 
 int /*<<< orphan*/  fsnotify_modify (struct file*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int stub1 (struct file*,scalar_t__,struct file*,scalar_t__,scalar_t__) ; 

int do_clone_file_range(struct file *file_in, loff_t pos_in,
			struct file *file_out, loff_t pos_out, u64 len)
{
	struct inode *inode_in = file_inode(file_in);
	struct inode *inode_out = file_inode(file_out);
	int ret;

	if (S_ISDIR(inode_in->i_mode) || S_ISDIR(inode_out->i_mode))
		return -EISDIR;
	if (!S_ISREG(inode_in->i_mode) || !S_ISREG(inode_out->i_mode))
		return -EINVAL;

	/*
	 * FICLONE/FICLONERANGE ioctls enforce that src and dest files are on
	 * the same mount. Practically, they only need to be on the same file
	 * system.
	 */
	if (inode_in->i_sb != inode_out->i_sb)
		return -EXDEV;

	if (!(file_in->f_mode & FMODE_READ) ||
	    !(file_out->f_mode & FMODE_WRITE) ||
	    (file_out->f_flags & O_APPEND))
		return -EBADF;

	if (!file_in->f_op->clone_file_range)
		return -EOPNOTSUPP;

	ret = clone_verify_area(file_in, pos_in, len, false);
	if (ret)
		return ret;

	ret = clone_verify_area(file_out, pos_out, len, true);
	if (ret)
		return ret;

	if (pos_in + len > i_size_read(inode_in))
		return -EINVAL;

	ret = file_in->f_op->clone_file_range(file_in, pos_in,
			file_out, pos_out, len);
	if (!ret) {
		fsnotify_access(file_in);
		fsnotify_modify(file_out);
	}

	return ret;
}