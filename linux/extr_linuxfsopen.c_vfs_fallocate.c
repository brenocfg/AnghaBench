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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; TYPE_2__* f_op; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {long (* fallocate ) (struct file*,int,scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 int EBADF ; 
 int EFBIG ; 
 int EINVAL ; 
 int EISDIR ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int ESPIPE ; 
 int ETXTBSY ; 
 int FALLOC_FL_COLLAPSE_RANGE ; 
 int FALLOC_FL_INSERT_RANGE ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int FALLOC_FL_SUPPORTED_MASK ; 
 int FALLOC_FL_UNSHARE_RANGE ; 
 int FALLOC_FL_ZERO_RANGE ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_end_write (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_start_write (struct file*) ; 
 int /*<<< orphan*/  fsnotify_modify (struct file*) ; 
 long security_file_permission (struct file*,int /*<<< orphan*/ ) ; 
 long stub1 (struct file*,int,scalar_t__,scalar_t__) ; 

int vfs_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
{
	struct inode *inode = file_inode(file);
	long ret;

	if (offset < 0 || len <= 0)
		return -EINVAL;

	/* Return error if mode is not supported */
	if (mode & ~FALLOC_FL_SUPPORTED_MASK)
		return -EOPNOTSUPP;

	/* Punch hole and zero range are mutually exclusive */
	if ((mode & (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_ZERO_RANGE)) ==
	    (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_ZERO_RANGE))
		return -EOPNOTSUPP;

	/* Punch hole must have keep size set */
	if ((mode & FALLOC_FL_PUNCH_HOLE) &&
	    !(mode & FALLOC_FL_KEEP_SIZE))
		return -EOPNOTSUPP;

	/* Collapse range should only be used exclusively. */
	if ((mode & FALLOC_FL_COLLAPSE_RANGE) &&
	    (mode & ~FALLOC_FL_COLLAPSE_RANGE))
		return -EINVAL;

	/* Insert range should only be used exclusively. */
	if ((mode & FALLOC_FL_INSERT_RANGE) &&
	    (mode & ~FALLOC_FL_INSERT_RANGE))
		return -EINVAL;

	/* Unshare range should only be used with allocate mode. */
	if ((mode & FALLOC_FL_UNSHARE_RANGE) &&
	    (mode & ~(FALLOC_FL_UNSHARE_RANGE | FALLOC_FL_KEEP_SIZE)))
		return -EINVAL;

	if (!(file->f_mode & FMODE_WRITE))
		return -EBADF;

	/*
	 * We can only allow pure fallocate on append only files
	 */
	if ((mode & ~FALLOC_FL_KEEP_SIZE) && IS_APPEND(inode))
		return -EPERM;

	if (IS_IMMUTABLE(inode))
		return -EPERM;

	/*
	 * We cannot allow any fallocate operation on an active swapfile
	 */
	if (IS_SWAPFILE(inode))
		return -ETXTBSY;

	/*
	 * Revalidate the write permissions, in case security policy has
	 * changed since the files were opened.
	 */
	ret = security_file_permission(file, MAY_WRITE);
	if (ret)
		return ret;

	if (S_ISFIFO(inode->i_mode))
		return -ESPIPE;

	if (S_ISDIR(inode->i_mode))
		return -EISDIR;

	if (!S_ISREG(inode->i_mode) && !S_ISBLK(inode->i_mode))
		return -ENODEV;

	/* Check for wrap through zero too */
	if (((offset + len) > inode->i_sb->s_maxbytes) || ((offset + len) < 0))
		return -EFBIG;

	if (!file->f_op->fallocate)
		return -EOPNOTSUPP;

	file_start_write(file);
	ret = file->f_op->fallocate(file, mode, offset, len);

	/*
	 * Create inotify and fanotify events.
	 *
	 * To keep the logic simple always create events if fallocate succeeds.
	 * This implies that events are even created if the file size remains
	 * unchanged, e.g. when using flag FALLOC_FL_KEEP_SIZE.
	 */
	if (ret == 0)
		fsnotify_modify(file);

	file_end_write(file);
	return ret;
}