#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfs_sb {scalar_t__ sb_magicnum; unsigned int sb_sectsize; } ;
struct xfs_mount {struct xfs_buf* m_sb_bp; int /*<<< orphan*/ * m_ddev_targp; struct xfs_sb m_sb; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf {struct xfs_buf_ops* b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTOBB (unsigned int) ; 
 int EFSBADCRC ; 
 int EFSCORRUPTED ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  XBF_NO_IOACCT ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int XFS_MFSI_QUIET ; 
 int /*<<< orphan*/  XFS_SB_DADDR ; 
 scalar_t__ XFS_SB_MAGIC ; 
 int xfs_buf_read_uncached (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,struct xfs_buf_ops const*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_unlock (struct xfs_buf*) ; 
 unsigned int xfs_getsize_buftarg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_reinit_percpu_counters (struct xfs_mount*) ; 
 struct xfs_buf_ops xfs_sb_buf_ops ; 
 int /*<<< orphan*/  xfs_sb_from_disk (struct xfs_sb*,int /*<<< orphan*/ ) ; 
 struct xfs_buf_ops xfs_sb_quiet_buf_ops ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,...) ; 

int
xfs_readsb(
	struct xfs_mount *mp,
	int		flags)
{
	unsigned int	sector_size;
	struct xfs_buf	*bp;
	struct xfs_sb	*sbp = &mp->m_sb;
	int		error;
	int		loud = !(flags & XFS_MFSI_QUIET);
	const struct xfs_buf_ops *buf_ops;

	ASSERT(mp->m_sb_bp == NULL);
	ASSERT(mp->m_ddev_targp != NULL);

	/*
	 * For the initial read, we must guess at the sector
	 * size based on the block device.  It's enough to
	 * get the sb_sectsize out of the superblock and
	 * then reread with the proper length.
	 * We don't verify it yet, because it may not be complete.
	 */
	sector_size = xfs_getsize_buftarg(mp->m_ddev_targp);
	buf_ops = NULL;

	/*
	 * Allocate a (locked) buffer to hold the superblock. This will be kept
	 * around at all times to optimize access to the superblock. Therefore,
	 * set XBF_NO_IOACCT to make sure it doesn't hold the buftarg count
	 * elevated.
	 */
reread:
	error = xfs_buf_read_uncached(mp->m_ddev_targp, XFS_SB_DADDR,
				      BTOBB(sector_size), XBF_NO_IOACCT, &bp,
				      buf_ops);
	if (error) {
		if (loud)
			xfs_warn(mp, "SB validate failed with error %d.", error);
		/* bad CRC means corrupted metadata */
		if (error == -EFSBADCRC)
			error = -EFSCORRUPTED;
		return error;
	}

	/*
	 * Initialize the mount structure from the superblock.
	 */
	xfs_sb_from_disk(sbp, XFS_BUF_TO_SBP(bp));

	/*
	 * If we haven't validated the superblock, do so now before we try
	 * to check the sector size and reread the superblock appropriately.
	 */
	if (sbp->sb_magicnum != XFS_SB_MAGIC) {
		if (loud)
			xfs_warn(mp, "Invalid superblock magic number");
		error = -EINVAL;
		goto release_buf;
	}

	/*
	 * We must be able to do sector-sized and sector-aligned IO.
	 */
	if (sector_size > sbp->sb_sectsize) {
		if (loud)
			xfs_warn(mp, "device supports %u byte sectors (not %u)",
				sector_size, sbp->sb_sectsize);
		error = -ENOSYS;
		goto release_buf;
	}

	if (buf_ops == NULL) {
		/*
		 * Re-read the superblock so the buffer is correctly sized,
		 * and properly verified.
		 */
		xfs_buf_relse(bp);
		sector_size = sbp->sb_sectsize;
		buf_ops = loud ? &xfs_sb_buf_ops : &xfs_sb_quiet_buf_ops;
		goto reread;
	}

	xfs_reinit_percpu_counters(mp);

	/* no need to be quiet anymore, so reset the buf ops */
	bp->b_ops = &xfs_sb_buf_ops;

	mp->m_sb_bp = bp;
	xfs_buf_unlock(bp);
	return 0;

release_buf:
	xfs_buf_relse(bp);
	return error;
}