#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  t_flags; } ;
typedef  TYPE_3__ xfs_trans_t ;
struct TYPE_12__ {TYPE_2__* i_itemp; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  int uint ;
struct inode {int i_state; int /*<<< orphan*/  i_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  li_flags; } ;
struct TYPE_10__ {int ili_fsync_fields; int ili_last_fields; int ili_fields; TYPE_1__ ili_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_I_VERSION (struct inode*) ; 
 int I_DIRTY_TIME ; 
 int I_DIRTY_TIME_EXPIRED ; 
 struct inode* VFS_I (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int XFS_ILOG_CORE ; 
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 scalar_t__ inode_maybe_inc_iversion (struct inode*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_isilocked (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
xfs_trans_log_inode(
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uint		flags)
{
	struct inode	*inode = VFS_I(ip);

	ASSERT(ip->i_itemp != NULL);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	/*
	 * Don't bother with i_lock for the I_DIRTY_TIME check here, as races
	 * don't matter - we either will need an extra transaction in 24 hours
	 * to log the timestamps, or will clear already cleared fields in the
	 * worst case.
	 */
	if (inode->i_state & (I_DIRTY_TIME | I_DIRTY_TIME_EXPIRED)) {
		spin_lock(&inode->i_lock);
		inode->i_state &= ~(I_DIRTY_TIME | I_DIRTY_TIME_EXPIRED);
		spin_unlock(&inode->i_lock);
	}

	/*
	 * Record the specific change for fdatasync optimisation. This
	 * allows fdatasync to skip log forces for inodes that are only
	 * timestamp dirty. We do this before the change count so that
	 * the core being logged in this case does not impact on fdatasync
	 * behaviour.
	 */
	ip->i_itemp->ili_fsync_fields |= flags;

	/*
	 * First time we log the inode in a transaction, bump the inode change
	 * counter if it is configured for this to occur. While we have the
	 * inode locked exclusively for metadata modification, we can usually
	 * avoid setting XFS_ILOG_CORE if no one has queried the value since
	 * the last time it was incremented. If we have XFS_ILOG_CORE already
	 * set however, then go ahead and bump the i_version counter
	 * unconditionally.
	 */
	if (!test_and_set_bit(XFS_LI_DIRTY, &ip->i_itemp->ili_item.li_flags) &&
	    IS_I_VERSION(VFS_I(ip))) {
		if (inode_maybe_inc_iversion(VFS_I(ip), flags & XFS_ILOG_CORE))
			flags |= XFS_ILOG_CORE;
	}

	tp->t_flags |= XFS_TRANS_DIRTY;

	/*
	 * Always OR in the bits from the ili_last_fields field.
	 * This is to coordinate with the xfs_iflush() and xfs_iflush_done()
	 * routines in the eventual clearing of the ili_fields bits.
	 * See the big comment in xfs_iflush() for an explanation of
	 * this coordination mechanism.
	 */
	flags |= ip->i_itemp->ili_last_fields;
	ip->i_itemp->ili_fields |= flags;
}