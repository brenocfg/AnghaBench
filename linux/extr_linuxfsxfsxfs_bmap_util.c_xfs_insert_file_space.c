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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  tr_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  NULLFSBLOCK ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 int /*<<< orphan*/  XFS_MMAPLOCK_EXCL ; 
 int /*<<< orphan*/  trace_xfs_insert_file_space (struct xfs_inode*) ; 
 int xfs_bmap_can_insert_extents (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_bmap_insert_extents (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int xfs_bmap_split_extent (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_isilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_prepare_shift (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xfs_insert_file_space(
	struct xfs_inode	*ip,
	loff_t			offset,
	loff_t			len)
{
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_trans	*tp;
	int			error;
	xfs_fileoff_t		stop_fsb = XFS_B_TO_FSB(mp, offset);
	xfs_fileoff_t		next_fsb = NULLFSBLOCK;
	xfs_fileoff_t		shift_fsb = XFS_B_TO_FSB(mp, len);
	bool			done = false;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_MMAPLOCK_EXCL));

	trace_xfs_insert_file_space(ip);

	error = xfs_bmap_can_insert_extents(ip, stop_fsb, shift_fsb);
	if (error)
		return error;

	error = xfs_prepare_shift(ip, offset);
	if (error)
		return error;

	/*
	 * The extent shifting code works on extent granularity. So, if stop_fsb
	 * is not the starting block of extent, we need to split the extent at
	 * stop_fsb.
	 */
	error = xfs_bmap_split_extent(ip, stop_fsb);
	if (error)
		return error;

	while (!error && !done) {
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_write, 0, 0, 0,
					&tp);
		if (error)
			break;

		xfs_ilock(ip, XFS_ILOCK_EXCL);
		xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
		error = xfs_bmap_insert_extents(tp, ip, &next_fsb, shift_fsb,
				&done, stop_fsb);
		if (error)
			goto out_trans_cancel;

		error = xfs_trans_commit(tp);
	}

	return error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	return error;
}