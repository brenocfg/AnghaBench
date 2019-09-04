#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_filblks_t ;
struct xfs_mount {int dummy; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 TYPE_1__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (TYPE_1__*) ; 
 int /*<<< orphan*/  inode_dio_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_xfs_reflink_unshare (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_reflink_unshare_error (struct xfs_inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_is_reflink_inode (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_reflink_dirty_extents (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_reflink_try_clear_inode_flag (struct xfs_inode*) ; 

int
xfs_reflink_unshare(
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
{
	struct xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		fbno;
	xfs_filblks_t		end;
	xfs_off_t		isize;
	int			error;

	if (!xfs_is_reflink_inode(ip))
		return 0;

	trace_xfs_reflink_unshare(ip, offset, len);

	inode_dio_wait(VFS_I(ip));

	/* Try to CoW the selected ranges */
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	fbno = XFS_B_TO_FSBT(mp, offset);
	isize = i_size_read(VFS_I(ip));
	end = XFS_B_TO_FSB(mp, offset + len);
	error = xfs_reflink_dirty_extents(ip, fbno, end, isize);
	if (error)
		goto out_unlock;
	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	/* Wait for the IO to finish */
	error = filemap_write_and_wait(VFS_I(ip)->i_mapping);
	if (error)
		goto out;

	/* Turn off the reflink flag if possible. */
	error = xfs_reflink_try_clear_inode_flag(ip);
	if (error)
		goto out;

	return 0;

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
out:
	trace_xfs_reflink_unshare_error(ip, error, _RET_IP_);
	return error;
}