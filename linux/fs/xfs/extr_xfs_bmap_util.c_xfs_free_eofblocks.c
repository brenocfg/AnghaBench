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
typedef  int /*<<< orphan*/  xfs_ufsize_t ;
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_filblks_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {TYPE_1__* m_super; } ;
struct xfs_inode {scalar_t__ i_delayed_blks; struct xfs_mount* i_mount; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; } ;
struct TYPE_4__ {int /*<<< orphan*/  tr_itruncate; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ HOLESTARTBLOCK ; 
 TYPE_2__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_BMAPI_NODISCARD ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOCK_SHARED ; 
 scalar_t__ XFS_ISIZE (struct xfs_inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (int /*<<< orphan*/ ) ; 
 int xfs_bmapi_read (struct xfs_inode*,scalar_t__,scalar_t__,struct xfs_bmbt_irec*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_clear_eofblocks_tag (struct xfs_inode*) ; 
 int xfs_itruncate_extents_flags (struct xfs_trans**,struct xfs_inode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (struct xfs_inode*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xfs_free_eofblocks(
	struct xfs_inode	*ip)
{
	struct xfs_trans	*tp;
	int			error;
	xfs_fileoff_t		end_fsb;
	xfs_fileoff_t		last_fsb;
	xfs_filblks_t		map_len;
	int			nimaps;
	struct xfs_bmbt_irec	imap;
	struct xfs_mount	*mp = ip->i_mount;

	/*
	 * Figure out if there are any blocks beyond the end
	 * of the file.  If not, then there is nothing to do.
	 */
	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufsize_t)XFS_ISIZE(ip));
	last_fsb = XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes);
	if (last_fsb <= end_fsb)
		return 0;
	map_len = last_fsb - end_fsb;

	nimaps = 1;
	xfs_ilock(ip, XFS_ILOCK_SHARED);
	error = xfs_bmapi_read(ip, end_fsb, map_len, &imap, &nimaps, 0);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);

	/*
	 * If there are blocks after the end of file, truncate the file to its
	 * current size to free them up.
	 */
	if (!error && (nimaps != 0) &&
	    (imap.br_startblock != HOLESTARTBLOCK ||
	     ip->i_delayed_blks)) {
		/*
		 * Attach the dquots to the inode up front.
		 */
		error = xfs_qm_dqattach(ip);
		if (error)
			return error;

		/* wait on dio to ensure i_size has settled */
		inode_dio_wait(VFS_I(ip));

		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0,
				&tp);
		if (error) {
			ASSERT(XFS_FORCED_SHUTDOWN(mp));
			return error;
		}

		xfs_ilock(ip, XFS_ILOCK_EXCL);
		xfs_trans_ijoin(tp, ip, 0);

		/*
		 * Do not update the on-disk file size.  If we update the
		 * on-disk file size and then the system crashes before the
		 * contents of the file are flushed to disk then the files
		 * may be full of holes (ie NULL files bug).
		 */
		error = xfs_itruncate_extents_flags(&tp, ip, XFS_DATA_FORK,
					XFS_ISIZE(ip), XFS_BMAPI_NODISCARD);
		if (error) {
			/*
			 * If we get an error at this point we simply don't
			 * bother truncating the file.
			 */
			xfs_trans_cancel(tp);
		} else {
			error = xfs_trans_commit(tp);
			if (!error)
				xfs_inode_clear_eofblocks_tag(ip);
		}

		xfs_iunlock(ip, XFS_ILOCK_EXCL);
	}
	return error;
}