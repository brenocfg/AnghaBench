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
struct xfs_mount {int /*<<< orphan*/  m_active_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_WAIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_quiesce (struct xfs_mount*) ; 
 int xfs_log_sbcount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_reclaim_inodes (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*) ; 

void
xfs_quiesce_attr(
	struct xfs_mount	*mp)
{
	int	error = 0;

	/* wait for all modifications to complete */
	while (atomic_read(&mp->m_active_trans) > 0)
		delay(100);

	/* force the log to unpin objects from the now complete transactions */
	xfs_log_force(mp, XFS_LOG_SYNC);

	/* reclaim inodes to do any IO before the freeze completes */
	xfs_reclaim_inodes(mp, 0);
	xfs_reclaim_inodes(mp, SYNC_WAIT);

	/* Push the superblock and write an unmount record */
	error = xfs_log_sbcount(mp);
	if (error)
		xfs_warn(mp, "xfs_attr_quiesce: failed to log sb changes. "
				"Frozen image may not be consistent.");
	/*
	 * Just warn here till VFS can correctly support
	 * read-only remount without racing.
	 */
	WARN_ON(atomic_read(&mp->m_active_trans) != 0);

	xfs_log_quiesce(mp);
}