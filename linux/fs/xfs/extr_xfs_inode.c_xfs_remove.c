#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_24__ {int m_flags; } ;
typedef  TYPE_1__ xfs_mount_t ;
struct TYPE_27__ {int /*<<< orphan*/  i_ino; TYPE_1__* i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  scalar_t__ uint ;
struct xfs_name {int dummy; } ;
struct TYPE_26__ {int /*<<< orphan*/  tr_remove; } ;
struct TYPE_25__ {int i_nlink; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOTEMPTY ; 
 TYPE_22__* M_RES (TYPE_1__*) ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_20__* VFS_I (TYPE_2__*) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (TYPE_1__*) ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int XFS_MOUNT_DIRSYNC ; 
 int XFS_MOUNT_WSYNC ; 
 scalar_t__ XFS_REMOVE_SPACE_RES (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_xfs_remove (TYPE_2__*,struct xfs_name*) ; 
 int /*<<< orphan*/  xfs_dir_isempty (TYPE_2__*) ; 
 int xfs_dir_removename (int /*<<< orphan*/ *,TYPE_2__*,struct xfs_name*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_droplink (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_filestream_deassociate (TYPE_2__*) ; 
 scalar_t__ xfs_inode_is_filestream (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_lock_two_inodes (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (TYPE_2__*) ; 
 int xfs_trans_alloc (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_remove(
	xfs_inode_t             *dp,
	struct xfs_name		*name,
	xfs_inode_t		*ip)
{
	xfs_mount_t		*mp = dp->i_mount;
	xfs_trans_t             *tp = NULL;
	int			is_dir = S_ISDIR(VFS_I(ip)->i_mode);
	int                     error = 0;
	uint			resblks;

	trace_xfs_remove(dp, name);

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	error = xfs_qm_dqattach(dp);
	if (error)
		goto std_return;

	error = xfs_qm_dqattach(ip);
	if (error)
		goto std_return;

	/*
	 * We try to get the real space reservation first,
	 * allowing for directory btree deletion(s) implying
	 * possible bmap insert(s).  If we can't get the space
	 * reservation then we use 0 instead, and avoid the bmap
	 * btree insert(s) in the directory code by, if the bmap
	 * insert tries to happen, instead trimming the LAST
	 * block from the directory.
	 */
	resblks = XFS_REMOVE_SPACE_RES(mp);
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_remove, resblks, 0, 0, &tp);
	if (error == -ENOSPC) {
		resblks = 0;
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_remove, 0, 0, 0,
				&tp);
	}
	if (error) {
		ASSERT(error != -ENOSPC);
		goto std_return;
	}

	xfs_lock_two_inodes(dp, XFS_ILOCK_EXCL, ip, XFS_ILOCK_EXCL);

	xfs_trans_ijoin(tp, dp, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	/*
	 * If we're removing a directory perform some additional validation.
	 */
	if (is_dir) {
		ASSERT(VFS_I(ip)->i_nlink >= 2);
		if (VFS_I(ip)->i_nlink != 2) {
			error = -ENOTEMPTY;
			goto out_trans_cancel;
		}
		if (!xfs_dir_isempty(ip)) {
			error = -ENOTEMPTY;
			goto out_trans_cancel;
		}

		/* Drop the link from ip's "..".  */
		error = xfs_droplink(tp, dp);
		if (error)
			goto out_trans_cancel;

		/* Drop the "." link from ip to self.  */
		error = xfs_droplink(tp, ip);
		if (error)
			goto out_trans_cancel;
	} else {
		/*
		 * When removing a non-directory we need to log the parent
		 * inode here.  For a directory this is done implicitly
		 * by the xfs_droplink call for the ".." entry.
		 */
		xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	}
	xfs_trans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

	/* Drop the link from dp to ip. */
	error = xfs_droplink(tp, ip);
	if (error)
		goto out_trans_cancel;

	error = xfs_dir_removename(tp, dp, name, ip->i_ino, resblks);
	if (error) {
		ASSERT(error != -ENOENT);
		goto out_trans_cancel;
	}

	/*
	 * If this is a synchronous mount, make sure that the
	 * remove transaction goes to disk before returning to
	 * the user.
	 */
	if (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC))
		xfs_trans_set_sync(tp);

	error = xfs_trans_commit(tp);
	if (error)
		goto std_return;

	if (is_dir && xfs_inode_is_filestream(ip))
		xfs_filestream_deassociate(ip);

	return 0;

 out_trans_cancel:
	xfs_trans_cancel(tp);
 std_return:
	return error;
}