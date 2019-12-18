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
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {scalar_t__ di_format; scalar_t__ di_nextents; } ;
struct xfs_inode {int /*<<< orphan*/  i_imap; TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct xfs_dinode {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int /*<<< orphan*/  XBF_TRYLOCK ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 scalar_t__ XFS_IFORK_MAXEXT (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  XFS_ISTALE ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_buf_ispinned (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_force_shutdown (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_iflags_test (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iflush_abort (struct xfs_inode*,int) ; 
 int xfs_iflush_cluster (struct xfs_inode*,struct xfs_buf*) ; 
 int xfs_iflush_int (struct xfs_inode*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_ifunlock (struct xfs_inode*) ; 
 int xfs_imap_to_bp (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xfs_dinode**,struct xfs_buf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_isiflocked (struct xfs_inode*) ; 
 int xfs_isilocked (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_iunpin_wait (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_iflush_count ; 

int
xfs_iflush(
	struct xfs_inode	*ip,
	struct xfs_buf		**bpp)
{
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_buf		*bp = NULL;
	struct xfs_dinode	*dip;
	int			error;

	XFS_STATS_INC(mp, xs_iflush_count);

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL|XFS_ILOCK_SHARED));
	ASSERT(xfs_isiflocked(ip));
	ASSERT(ip->i_d.di_format != XFS_DINODE_FMT_BTREE ||
	       ip->i_d.di_nextents > XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK));

	*bpp = NULL;

	xfs_iunpin_wait(ip);

	/*
	 * For stale inodes we cannot rely on the backing buffer remaining
	 * stale in cache for the remaining life of the stale inode and so
	 * xfs_imap_to_bp() below may give us a buffer that no longer contains
	 * inodes below. We have to check this after ensuring the inode is
	 * unpinned so that it is safe to reclaim the stale inode after the
	 * flush call.
	 */
	if (xfs_iflags_test(ip, XFS_ISTALE)) {
		xfs_ifunlock(ip);
		return 0;
	}

	/*
	 * This may have been unpinned because the filesystem is shutting
	 * down forcibly. If that's the case we must not write this inode
	 * to disk, because the log record didn't make it to disk.
	 *
	 * We also have to remove the log item from the AIL in this case,
	 * as we wait for an empty AIL as part of the unmount process.
	 */
	if (XFS_FORCED_SHUTDOWN(mp)) {
		error = -EIO;
		goto abort_out;
	}

	/*
	 * Get the buffer containing the on-disk inode. We are doing a try-lock
	 * operation here, so we may get  an EAGAIN error. In that case, we
	 * simply want to return with the inode still dirty.
	 *
	 * If we get any other error, we effectively have a corruption situation
	 * and we cannot flush the inode, so we treat it the same as failing
	 * xfs_iflush_int().
	 */
	error = xfs_imap_to_bp(mp, NULL, &ip->i_imap, &dip, &bp, XBF_TRYLOCK,
			       0);
	if (error == -EAGAIN) {
		xfs_ifunlock(ip);
		return error;
	}
	if (error)
		goto corrupt_out;

	/*
	 * First flush out the inode that xfs_iflush was called with.
	 */
	error = xfs_iflush_int(ip, bp);
	if (error)
		goto corrupt_out;

	/*
	 * If the buffer is pinned then push on the log now so we won't
	 * get stuck waiting in the write for too long.
	 */
	if (xfs_buf_ispinned(bp))
		xfs_log_force(mp, 0);

	/*
	 * inode clustering: try to gather other inodes into this write
	 *
	 * Note: Any error during clustering will result in the filesystem
	 * being shut down and completion callbacks run on the cluster buffer.
	 * As we have already flushed and attached this inode to the buffer,
	 * it has already been aborted and released by xfs_iflush_cluster() and
	 * so we have no further error handling to do here.
	 */
	error = xfs_iflush_cluster(ip, bp);
	if (error)
		return error;

	*bpp = bp;
	return 0;

corrupt_out:
	if (bp)
		xfs_buf_relse(bp);
	xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
abort_out:
	/* abort the corrupt inode, as it was not attached to the buffer */
	xfs_iflush_abort(ip, false);
	return error;
}