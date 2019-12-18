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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  xs_kobj; } ;
struct xfs_mount {int /*<<< orphan*/  m_kobj; TYPE_1__ m_stats; int /*<<< orphan*/  m_reclaim_work; int /*<<< orphan*/  m_ail; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_rootip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_WAIT ; 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 int /*<<< orphan*/  XFS_MOUNT_UNMOUNTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ail_push_all_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_discard_wq ; 
 int /*<<< orphan*/  xfs_error_sysfs_del (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_errortag_clearall (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_errortag_del (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_extent_busy_wait_all (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_free_perag (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_fs_unreserve_ag_blocks (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_health_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_irele (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_log_sbcount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_log_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_unmount_quotas (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_reclaim_inodes (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_reserve_blocks (struct xfs_mount*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rtunmount_inodes (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_stop_block_reaping (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_sysfs_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_uuid_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*) ; 

void
xfs_unmountfs(
	struct xfs_mount	*mp)
{
	uint64_t		resblks;
	int			error;

	xfs_stop_block_reaping(mp);
	xfs_fs_unreserve_ag_blocks(mp);
	xfs_qm_unmount_quotas(mp);
	xfs_rtunmount_inodes(mp);
	xfs_irele(mp->m_rootip);

	/*
	 * We can potentially deadlock here if we have an inode cluster
	 * that has been freed has its buffer still pinned in memory because
	 * the transaction is still sitting in a iclog. The stale inodes
	 * on that buffer will have their flush locks held until the
	 * transaction hits the disk and the callbacks run. the inode
	 * flush takes the flush lock unconditionally and with nothing to
	 * push out the iclog we will never get that unlocked. hence we
	 * need to force the log first.
	 */
	xfs_log_force(mp, XFS_LOG_SYNC);

	/*
	 * Wait for all busy extents to be freed, including completion of
	 * any discard operation.
	 */
	xfs_extent_busy_wait_all(mp);
	flush_workqueue(xfs_discard_wq);

	/*
	 * We now need to tell the world we are unmounting. This will allow
	 * us to detect that the filesystem is going away and we should error
	 * out anything that we have been retrying in the background. This will
	 * prevent neverending retries in AIL pushing from hanging the unmount.
	 */
	mp->m_flags |= XFS_MOUNT_UNMOUNTING;

	/*
	 * Flush all pending changes from the AIL.
	 */
	xfs_ail_push_all_sync(mp->m_ail);

	/*
	 * And reclaim all inodes.  At this point there should be no dirty
	 * inodes and none should be pinned or locked, but use synchronous
	 * reclaim just to be sure. We can stop background inode reclaim
	 * here as well if it is still running.
	 */
	cancel_delayed_work_sync(&mp->m_reclaim_work);
	xfs_reclaim_inodes(mp, SYNC_WAIT);
	xfs_health_unmount(mp);

	xfs_qm_unmount(mp);

	/*
	 * Unreserve any blocks we have so that when we unmount we don't account
	 * the reserved free space as used. This is really only necessary for
	 * lazy superblock counting because it trusts the incore superblock
	 * counters to be absolutely correct on clean unmount.
	 *
	 * We don't bother correcting this elsewhere for lazy superblock
	 * counting because on mount of an unclean filesystem we reconstruct the
	 * correct counter value and this is irrelevant.
	 *
	 * For non-lazy counter filesystems, this doesn't matter at all because
	 * we only every apply deltas to the superblock and hence the incore
	 * value does not matter....
	 */
	resblks = 0;
	error = xfs_reserve_blocks(mp, &resblks, NULL);
	if (error)
		xfs_warn(mp, "Unable to free reserved block pool. "
				"Freespace may not be correct on next mount.");

	error = xfs_log_sbcount(mp);
	if (error)
		xfs_warn(mp, "Unable to update superblock counters. "
				"Freespace may not be correct on next mount.");


	xfs_log_unmount(mp);
	xfs_da_unmount(mp);
	xfs_uuid_unmount(mp);

#if defined(DEBUG)
	xfs_errortag_clearall(mp);
#endif
	xfs_free_perag(mp);

	xfs_errortag_del(mp);
	xfs_error_sysfs_del(mp);
	xfs_sysfs_del(&mp->m_stats.xs_kobj);
	xfs_sysfs_del(&mp->m_kobj);
}