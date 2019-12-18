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
typedef  scalar_t__ xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_inode {int /*<<< orphan*/  i_pdquot; int /*<<< orphan*/  i_gdquot; int /*<<< orphan*/  i_udquot; struct xfs_mount* i_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_DIOSTRAT_SPACE_RES (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 int /*<<< orphan*/  XFS_MMAPLOCK_EXCL ; 
 int /*<<< orphan*/  XFS_QMOPT_RES_REGBLKS ; 
 int /*<<< orphan*/  trace_xfs_collapse_file_space (struct xfs_inode*) ; 
 int xfs_bmap_collapse_extents (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int xfs_free_file_space (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_isilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_prepare_shift (struct xfs_inode*,scalar_t__) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve_quota (struct xfs_trans*,struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_collapse_file_space(
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
{
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_trans	*tp;
	int			error;
	xfs_fileoff_t		next_fsb = XFS_B_TO_FSB(mp, offset + len);
	xfs_fileoff_t		shift_fsb = XFS_B_TO_FSB(mp, len);
	uint			resblks = XFS_DIOSTRAT_SPACE_RES(mp, 0);
	bool			done = false;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_MMAPLOCK_EXCL));

	trace_xfs_collapse_file_space(ip);

	error = xfs_free_file_space(ip, offset, len);
	if (error)
		return error;

	error = xfs_prepare_shift(ip, offset);
	if (error)
		return error;

	while (!error && !done) {
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_write, resblks, 0, 0,
					&tp);
		if (error)
			break;

		xfs_ilock(ip, XFS_ILOCK_EXCL);
		error = xfs_trans_reserve_quota(tp, mp, ip->i_udquot,
				ip->i_gdquot, ip->i_pdquot, resblks, 0,
				XFS_QMOPT_RES_REGBLKS);
		if (error)
			goto out_trans_cancel;
		xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

		error = xfs_bmap_collapse_extents(tp, ip, &next_fsb, shift_fsb,
				&done);
		if (error)
			goto out_trans_cancel;

		error = xfs_trans_commit(tp);
	}

	return error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	return error;
}