#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_filblks_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
struct TYPE_9__ {char* b_addr; int /*<<< orphan*/ * b_ops; } ;
typedef  TYPE_2__ xfs_buf_t ;
typedef  int umode_t ;
typedef  scalar_t__ uint ;
struct xfs_trans {int dummy; } ;
struct xfs_name {int /*<<< orphan*/  len; } ;
struct xfs_mount {int m_flags; int /*<<< orphan*/  m_ddev_targp; } ;
struct TYPE_8__ {int di_flags; int di_size; int /*<<< orphan*/  di_format; int /*<<< orphan*/  di_version; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct xfs_dquot {int dummy; } ;
struct xfs_bmbt_irec {int /*<<< orphan*/  br_blockcount; int /*<<< orphan*/  br_startblock; } ;
typedef  int /*<<< orphan*/  prid_t ;
struct TYPE_10__ {int /*<<< orphan*/  tr_symlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTOBB (int) ; 
 int EIO ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int EPERM ; 
 TYPE_7__* M_RES (struct xfs_mount*) ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XFS_BLFT_SYMLINK_BUF ; 
 int /*<<< orphan*/  XFS_BMAPI_METADATA ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DIFLAG_NOSYMLINKS ; 
 int /*<<< orphan*/  XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int XFS_FSB_TO_B (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IALLOC_SPACE_RES (struct xfs_mount*) ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int XFS_IFORK_DSIZE (struct xfs_inode*) ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_PARENT ; 
 int XFS_ILOG_CORE ; 
 int XFS_ILOG_DDATA ; 
 int XFS_LITINO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_MOUNT_DIRSYNC ; 
 int XFS_MOUNT_WSYNC ; 
 int XFS_QMOPT_INHERIT ; 
 int XFS_QMOPT_QUOTALL ; 
 int XFS_SYMLINK_BUF_SPACE (struct xfs_mount*,int) ; 
 int XFS_SYMLINK_MAPS ; 
 int XFS_SYMLINK_MAXLEN ; 
 scalar_t__ XFS_SYMLINK_SPACE_RES (struct xfs_mount*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int min (int,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  trace_xfs_symlink (struct xfs_inode*,struct xfs_name*) ; 
 int xfs_bmapi_write (struct xfs_trans*,struct xfs_inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct xfs_bmbt_irec*,int*) ; 
 int xfs_dir_createname (struct xfs_trans*,struct xfs_inode*,struct xfs_name*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_dir_ialloc (struct xfs_trans**,struct xfs_inode*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inode**) ; 
 int /*<<< orphan*/  xfs_finish_inode_setup (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_get_initial_prid (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_init_local_fork (struct xfs_inode*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  xfs_irele (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_kgid_to_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_kuid_to_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_dqrele (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_qm_vop_create_dqattach (struct xfs_trans*,struct xfs_inode*,struct xfs_dquot*,struct xfs_dquot*,struct xfs_dquot*) ; 
 int xfs_qm_vop_dqalloc (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_dquot**,struct xfs_dquot**,struct xfs_dquot**) ; 
 scalar_t__ xfs_symlink_blocks (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  xfs_symlink_buf_ops ; 
 int /*<<< orphan*/  xfs_symlink_hdr_set (struct xfs_mount*,int /*<<< orphan*/ ,int,int,TYPE_2__*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 TYPE_2__* xfs_trans_get_buf (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (struct xfs_trans*,struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int) ; 
 int xfs_trans_reserve_quota (struct xfs_trans*,struct xfs_mount*,struct xfs_dquot*,struct xfs_dquot*,struct xfs_dquot*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

int
xfs_symlink(
	struct xfs_inode	*dp,
	struct xfs_name		*link_name,
	const char		*target_path,
	umode_t			mode,
	struct xfs_inode	**ipp)
{
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_trans	*tp = NULL;
	struct xfs_inode	*ip = NULL;
	int			error = 0;
	int			pathlen;
	bool                    unlock_dp_on_error = false;
	xfs_fileoff_t		first_fsb;
	xfs_filblks_t		fs_blocks;
	int			nmaps;
	struct xfs_bmbt_irec	mval[XFS_SYMLINK_MAPS];
	xfs_daddr_t		d;
	const char		*cur_chunk;
	int			byte_cnt;
	int			n;
	xfs_buf_t		*bp;
	prid_t			prid;
	struct xfs_dquot	*udqp = NULL;
	struct xfs_dquot	*gdqp = NULL;
	struct xfs_dquot	*pdqp = NULL;
	uint			resblks;

	*ipp = NULL;

	trace_xfs_symlink(dp, link_name);

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	/*
	 * Check component lengths of the target path name.
	 */
	pathlen = strlen(target_path);
	if (pathlen >= XFS_SYMLINK_MAXLEN)      /* total string too long */
		return -ENAMETOOLONG;
	ASSERT(pathlen > 0);

	udqp = gdqp = NULL;
	prid = xfs_get_initial_prid(dp);

	/*
	 * Make sure that we have allocated dquot(s) on disk.
	 */
	error = xfs_qm_vop_dqalloc(dp,
			xfs_kuid_to_uid(current_fsuid()),
			xfs_kgid_to_gid(current_fsgid()), prid,
			XFS_QMOPT_QUOTALL | XFS_QMOPT_INHERIT,
			&udqp, &gdqp, &pdqp);
	if (error)
		return error;

	/*
	 * The symlink will fit into the inode data fork?
	 * There can't be any attributes so we get the whole variable part.
	 */
	if (pathlen <= XFS_LITINO(mp, dp->i_d.di_version))
		fs_blocks = 0;
	else
		fs_blocks = xfs_symlink_blocks(mp, pathlen);
	resblks = XFS_SYMLINK_SPACE_RES(mp, link_name->len, fs_blocks);

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_symlink, resblks, 0, 0, &tp);
	if (error)
		goto out_release_inode;

	xfs_ilock(dp, XFS_ILOCK_EXCL | XFS_ILOCK_PARENT);
	unlock_dp_on_error = true;

	/*
	 * Check whether the directory allows new symlinks or not.
	 */
	if (dp->i_d.di_flags & XFS_DIFLAG_NOSYMLINKS) {
		error = -EPERM;
		goto out_trans_cancel;
	}

	/*
	 * Reserve disk quota : blocks and inode.
	 */
	error = xfs_trans_reserve_quota(tp, mp, udqp, gdqp,
						pdqp, resblks, 1, 0);
	if (error)
		goto out_trans_cancel;

	/*
	 * Allocate an inode for the symlink.
	 */
	error = xfs_dir_ialloc(&tp, dp, S_IFLNK | (mode & ~S_IFMT), 1, 0,
			       prid, &ip);
	if (error)
		goto out_trans_cancel;

	/*
	 * Now we join the directory inode to the transaction.  We do not do it
	 * earlier because xfs_dir_ialloc might commit the previous transaction
	 * (and release all the locks).  An error from here on will result in
	 * the transaction cancel unlocking dp so don't do it explicitly in the
	 * error path.
	 */
	xfs_trans_ijoin(tp, dp, XFS_ILOCK_EXCL);
	unlock_dp_on_error = false;

	/*
	 * Also attach the dquot(s) to it, if applicable.
	 */
	xfs_qm_vop_create_dqattach(tp, ip, udqp, gdqp, pdqp);

	if (resblks)
		resblks -= XFS_IALLOC_SPACE_RES(mp);
	/*
	 * If the symlink will fit into the inode, write it inline.
	 */
	if (pathlen <= XFS_IFORK_DSIZE(ip)) {
		xfs_init_local_fork(ip, XFS_DATA_FORK, target_path, pathlen);

		ip->i_d.di_size = pathlen;
		ip->i_d.di_format = XFS_DINODE_FMT_LOCAL;
		xfs_trans_log_inode(tp, ip, XFS_ILOG_DDATA | XFS_ILOG_CORE);
	} else {
		int	offset;

		first_fsb = 0;
		nmaps = XFS_SYMLINK_MAPS;

		error = xfs_bmapi_write(tp, ip, first_fsb, fs_blocks,
				  XFS_BMAPI_METADATA, resblks, mval, &nmaps);
		if (error)
			goto out_trans_cancel;

		if (resblks)
			resblks -= fs_blocks;
		ip->i_d.di_size = pathlen;
		xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

		cur_chunk = target_path;
		offset = 0;
		for (n = 0; n < nmaps; n++) {
			char	*buf;

			d = XFS_FSB_TO_DADDR(mp, mval[n].br_startblock);
			byte_cnt = XFS_FSB_TO_B(mp, mval[n].br_blockcount);
			bp = xfs_trans_get_buf(tp, mp->m_ddev_targp, d,
					       BTOBB(byte_cnt), 0);
			if (!bp) {
				error = -ENOMEM;
				goto out_trans_cancel;
			}
			bp->b_ops = &xfs_symlink_buf_ops;

			byte_cnt = XFS_SYMLINK_BUF_SPACE(mp, byte_cnt);
			byte_cnt = min(byte_cnt, pathlen);

			buf = bp->b_addr;
			buf += xfs_symlink_hdr_set(mp, ip->i_ino, offset,
						   byte_cnt, bp);

			memcpy(buf, cur_chunk, byte_cnt);

			cur_chunk += byte_cnt;
			pathlen -= byte_cnt;
			offset += byte_cnt;

			xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SYMLINK_BUF);
			xfs_trans_log_buf(tp, bp, 0, (buf + byte_cnt - 1) -
							(char *)bp->b_addr);
		}
		ASSERT(pathlen == 0);
	}

	/*
	 * Create the directory entry for the symlink.
	 */
	error = xfs_dir_createname(tp, dp, link_name, ip->i_ino, resblks);
	if (error)
		goto out_trans_cancel;
	xfs_trans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);

	/*
	 * If this is a synchronous mount, make sure that the
	 * symlink transaction goes to disk before returning to
	 * the user.
	 */
	if (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC)) {
		xfs_trans_set_sync(tp);
	}

	error = xfs_trans_commit(tp);
	if (error)
		goto out_release_inode;

	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	*ipp = ip;
	return 0;

out_trans_cancel:
	xfs_trans_cancel(tp);
out_release_inode:
	/*
	 * Wait until after the current transaction is aborted to finish the
	 * setup of the inode and release the inode.  This prevents recursive
	 * transactions and deadlocks from xfs_inactive.
	 */
	if (ip) {
		xfs_finish_inode_setup(ip);
		xfs_irele(ip);
	}

	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	if (unlock_dp_on_error)
		xfs_iunlock(dp, XFS_ILOCK_EXCL);
	return error;
}