#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int l_whence; scalar_t__ l_start; scalar_t__ l_len; } ;
typedef  TYPE_2__ xfs_flock64_t ;
typedef  int uint ;
struct xfs_inode {int dummy; } ;
struct inode {int i_flags; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct iattr {scalar_t__ ia_size; int /*<<< orphan*/  ia_valid; } ;
struct file {int f_mode; int f_flags; int /*<<< orphan*/  f_pos; } ;
typedef  enum xfs_prealloc_flags { ____Placeholder_xfs_prealloc_flags } xfs_prealloc_flags ;
struct TYPE_4__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  BREAK_UNMAP ; 
 int EBADF ; 
 int EINVAL ; 
 int EPERM ; 
 int FMODE_NOCMTIME ; 
 int FMODE_WRITE ; 
 int O_DSYNC ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BMAPI_PREALLOC ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
#define  XFS_IOC_ALLOCSP 136 
#define  XFS_IOC_ALLOCSP64 135 
#define  XFS_IOC_FREESP 134 
#define  XFS_IOC_FREESP64 133 
#define  XFS_IOC_RESVSP 132 
#define  XFS_IOC_RESVSP64 131 
#define  XFS_IOC_UNRESVSP 130 
#define  XFS_IOC_UNRESVSP64 129 
#define  XFS_IOC_ZERO_RANGE 128 
 int XFS_IOLOCK_EXCL ; 
 scalar_t__ XFS_ISIZE (struct xfs_inode*) ; 
 int XFS_MMAPLOCK_EXCL ; 
 int XFS_PREALLOC_CLEAR ; 
 int XFS_PREALLOC_INVISIBLE ; 
 int XFS_PREALLOC_SET ; 
 int XFS_PREALLOC_SYNC ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int xfs_alloc_file_space (struct xfs_inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int xfs_break_layouts (struct inode*,int*,int /*<<< orphan*/ ) ; 
 int xfs_free_file_space (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int) ; 
 int xfs_update_prealloc_flags (struct xfs_inode*,int) ; 
 int xfs_vn_setattr_size (int /*<<< orphan*/ ,struct iattr*) ; 
 int xfs_zero_file_space (struct xfs_inode*,scalar_t__,scalar_t__) ; 

int
xfs_ioc_space(
	struct file		*filp,
	unsigned int		cmd,
	xfs_flock64_t		*bf)
{
	struct inode		*inode = file_inode(filp);
	struct xfs_inode	*ip = XFS_I(inode);
	struct iattr		iattr;
	enum xfs_prealloc_flags	flags = 0;
	uint			iolock = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	int			error;

	if (inode->i_flags & (S_IMMUTABLE|S_APPEND))
		return -EPERM;

	if (!(filp->f_mode & FMODE_WRITE))
		return -EBADF;

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	if (filp->f_flags & O_DSYNC)
		flags |= XFS_PREALLOC_SYNC;
	if (filp->f_mode & FMODE_NOCMTIME)
		flags |= XFS_PREALLOC_INVISIBLE;

	error = mnt_want_write_file(filp);
	if (error)
		return error;

	xfs_ilock(ip, iolock);
	error = xfs_break_layouts(inode, &iolock, BREAK_UNMAP);
	if (error)
		goto out_unlock;

	switch (bf->l_whence) {
	case 0: /*SEEK_SET*/
		break;
	case 1: /*SEEK_CUR*/
		bf->l_start += filp->f_pos;
		break;
	case 2: /*SEEK_END*/
		bf->l_start += XFS_ISIZE(ip);
		break;
	default:
		error = -EINVAL;
		goto out_unlock;
	}

	/*
	 * length of <= 0 for resv/unresv/zero is invalid.  length for
	 * alloc/free is ignored completely and we have no idea what userspace
	 * might have set it to, so set it to zero to allow range
	 * checks to pass.
	 */
	switch (cmd) {
	case XFS_IOC_ZERO_RANGE:
	case XFS_IOC_RESVSP:
	case XFS_IOC_RESVSP64:
	case XFS_IOC_UNRESVSP:
	case XFS_IOC_UNRESVSP64:
		if (bf->l_len <= 0) {
			error = -EINVAL;
			goto out_unlock;
		}
		break;
	default:
		bf->l_len = 0;
		break;
	}

	if (bf->l_start < 0 ||
	    bf->l_start > inode->i_sb->s_maxbytes ||
	    bf->l_start + bf->l_len < 0 ||
	    bf->l_start + bf->l_len >= inode->i_sb->s_maxbytes) {
		error = -EINVAL;
		goto out_unlock;
	}

	switch (cmd) {
	case XFS_IOC_ZERO_RANGE:
		flags |= XFS_PREALLOC_SET;
		error = xfs_zero_file_space(ip, bf->l_start, bf->l_len);
		break;
	case XFS_IOC_RESVSP:
	case XFS_IOC_RESVSP64:
		flags |= XFS_PREALLOC_SET;
		error = xfs_alloc_file_space(ip, bf->l_start, bf->l_len,
						XFS_BMAPI_PREALLOC);
		break;
	case XFS_IOC_UNRESVSP:
	case XFS_IOC_UNRESVSP64:
		error = xfs_free_file_space(ip, bf->l_start, bf->l_len);
		break;
	case XFS_IOC_ALLOCSP:
	case XFS_IOC_ALLOCSP64:
	case XFS_IOC_FREESP:
	case XFS_IOC_FREESP64:
		flags |= XFS_PREALLOC_CLEAR;
		if (bf->l_start > XFS_ISIZE(ip)) {
			error = xfs_alloc_file_space(ip, XFS_ISIZE(ip),
					bf->l_start - XFS_ISIZE(ip), 0);
			if (error)
				goto out_unlock;
		}

		iattr.ia_valid = ATTR_SIZE;
		iattr.ia_size = bf->l_start;

		error = xfs_vn_setattr_size(file_dentry(filp), &iattr);
		break;
	default:
		ASSERT(0);
		error = -EINVAL;
	}

	if (error)
		goto out_unlock;

	error = xfs_update_prealloc_flags(ip, flags);

out_unlock:
	xfs_iunlock(ip, iolock);
	mnt_drop_write_file(filp);
	return error;
}