#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_qoff_logitem_t ;
struct TYPE_11__ {int sb_qflags; } ;
struct TYPE_12__ {int m_qflags; int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; struct xfs_quotainfo* m_quotainfo; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int uint ;
struct xfs_quotainfo {int /*<<< orphan*/  qi_quotaofflock; int /*<<< orphan*/ * qi_pquotaip; int /*<<< orphan*/ * qi_gquotaip; int /*<<< orphan*/ * qi_uquotaip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct xfs_quotainfo*) ; 
 int EEXIST ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int XFS_ALL_QUOTA_ACCT ; 
 int XFS_ALL_QUOTA_ENFD ; 
 int XFS_GQUOTA_ACCT ; 
 int XFS_GQUOTA_ACTIVE ; 
 int XFS_GQUOTA_CHKD ; 
 int XFS_GQUOTA_ENFD ; 
 int XFS_PQUOTA_ACCT ; 
 int XFS_PQUOTA_ACTIVE ; 
 int XFS_PQUOTA_CHKD ; 
 int XFS_PQUOTA_ENFD ; 
 int XFS_QMOPT_GQUOTA ; 
 int XFS_QMOPT_PQUOTA ; 
 int XFS_QMOPT_UQUOTA ; 
 int XFS_UQUOTA_ACCT ; 
 int XFS_UQUOTA_ACTIVE ; 
 int XFS_UQUOTA_CHKD ; 
 int XFS_UQUOTA_ENFD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_force_shutdown (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_irele (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_qm_destroy_quotainfo (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_qm_dqpurge_all (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xfs_qm_dqrele_all_inodes (TYPE_2__*,int) ; 
 int xfs_qm_log_quotaoff (TYPE_2__*,int /*<<< orphan*/ **,int) ; 
 int xfs_qm_log_quotaoff_end (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int xfs_sync_sb (TYPE_2__*,int) ; 

int
xfs_qm_scall_quotaoff(
	xfs_mount_t		*mp,
	uint			flags)
{
	struct xfs_quotainfo	*q = mp->m_quotainfo;
	uint			dqtype;
	int			error;
	uint			inactivate_flags;
	xfs_qoff_logitem_t	*qoffstart;

	/*
	 * No file system can have quotas enabled on disk but not in core.
	 * Note that quota utilities (like quotaoff) _expect_
	 * errno == -EEXIST here.
	 */
	if ((mp->m_qflags & flags) == 0)
		return -EEXIST;
	error = 0;

	flags &= (XFS_ALL_QUOTA_ACCT | XFS_ALL_QUOTA_ENFD);

	/*
	 * We don't want to deal with two quotaoffs messing up each other,
	 * so we're going to serialize it. quotaoff isn't exactly a performance
	 * critical thing.
	 * If quotaoff, then we must be dealing with the root filesystem.
	 */
	ASSERT(q);
	mutex_lock(&q->qi_quotaofflock);

	/*
	 * If we're just turning off quota enforcement, change mp and go.
	 */
	if ((flags & XFS_ALL_QUOTA_ACCT) == 0) {
		mp->m_qflags &= ~(flags);

		spin_lock(&mp->m_sb_lock);
		mp->m_sb.sb_qflags = mp->m_qflags;
		spin_unlock(&mp->m_sb_lock);
		mutex_unlock(&q->qi_quotaofflock);

		/* XXX what to do if error ? Revert back to old vals incore ? */
		return xfs_sync_sb(mp, false);
	}

	dqtype = 0;
	inactivate_flags = 0;
	/*
	 * If accounting is off, we must turn enforcement off, clear the
	 * quota 'CHKD' certificate to make it known that we have to
	 * do a quotacheck the next time this quota is turned on.
	 */
	if (flags & XFS_UQUOTA_ACCT) {
		dqtype |= XFS_QMOPT_UQUOTA;
		flags |= (XFS_UQUOTA_CHKD | XFS_UQUOTA_ENFD);
		inactivate_flags |= XFS_UQUOTA_ACTIVE;
	}
	if (flags & XFS_GQUOTA_ACCT) {
		dqtype |= XFS_QMOPT_GQUOTA;
		flags |= (XFS_GQUOTA_CHKD | XFS_GQUOTA_ENFD);
		inactivate_flags |= XFS_GQUOTA_ACTIVE;
	}
	if (flags & XFS_PQUOTA_ACCT) {
		dqtype |= XFS_QMOPT_PQUOTA;
		flags |= (XFS_PQUOTA_CHKD | XFS_PQUOTA_ENFD);
		inactivate_flags |= XFS_PQUOTA_ACTIVE;
	}

	/*
	 * Nothing to do?  Don't complain. This happens when we're just
	 * turning off quota enforcement.
	 */
	if ((mp->m_qflags & flags) == 0)
		goto out_unlock;

	/*
	 * Write the LI_QUOTAOFF log record, and do SB changes atomically,
	 * and synchronously. If we fail to write, we should abort the
	 * operation as it cannot be recovered safely if we crash.
	 */
	error = xfs_qm_log_quotaoff(mp, &qoffstart, flags);
	if (error)
		goto out_unlock;

	/*
	 * Next we clear the XFS_MOUNT_*DQ_ACTIVE bit(s) in the mount struct
	 * to take care of the race between dqget and quotaoff. We don't take
	 * any special locks to reset these bits. All processes need to check
	 * these bits *after* taking inode lock(s) to see if the particular
	 * quota type is in the process of being turned off. If *ACTIVE, it is
	 * guaranteed that all dquot structures and all quotainode ptrs will all
	 * stay valid as long as that inode is kept locked.
	 *
	 * There is no turning back after this.
	 */
	mp->m_qflags &= ~inactivate_flags;

	/*
	 * Give back all the dquot reference(s) held by inodes.
	 * Here we go thru every single incore inode in this file system, and
	 * do a dqrele on the i_udquot/i_gdquot that it may have.
	 * Essentially, as long as somebody has an inode locked, this guarantees
	 * that quotas will not be turned off. This is handy because in a
	 * transaction once we lock the inode(s) and check for quotaon, we can
	 * depend on the quota inodes (and other things) being valid as long as
	 * we keep the lock(s).
	 */
	xfs_qm_dqrele_all_inodes(mp, flags);

	/*
	 * Next we make the changes in the quota flag in the mount struct.
	 * This isn't protected by a particular lock directly, because we
	 * don't want to take a mrlock every time we depend on quotas being on.
	 */
	mp->m_qflags &= ~flags;

	/*
	 * Go through all the dquots of this file system and purge them,
	 * according to what was turned off.
	 */
	xfs_qm_dqpurge_all(mp, dqtype);

	/*
	 * Transactions that had started before ACTIVE state bit was cleared
	 * could have logged many dquots, so they'd have higher LSNs than
	 * the first QUOTAOFF log record does. If we happen to crash when
	 * the tail of the log has gone past the QUOTAOFF record, but
	 * before the last dquot modification, those dquots __will__
	 * recover, and that's not good.
	 *
	 * So, we have QUOTAOFF start and end logitems; the start
	 * logitem won't get overwritten until the end logitem appears...
	 */
	error = xfs_qm_log_quotaoff_end(mp, qoffstart, flags);
	if (error) {
		/* We're screwed now. Shutdown is the only option. */
		xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
		goto out_unlock;
	}

	/*
	 * If all quotas are completely turned off, close shop.
	 */
	if (mp->m_qflags == 0) {
		mutex_unlock(&q->qi_quotaofflock);
		xfs_qm_destroy_quotainfo(mp);
		return 0;
	}

	/*
	 * Release our quotainode references if we don't need them anymore.
	 */
	if ((dqtype & XFS_QMOPT_UQUOTA) && q->qi_uquotaip) {
		xfs_irele(q->qi_uquotaip);
		q->qi_uquotaip = NULL;
	}
	if ((dqtype & XFS_QMOPT_GQUOTA) && q->qi_gquotaip) {
		xfs_irele(q->qi_gquotaip);
		q->qi_gquotaip = NULL;
	}
	if ((dqtype & XFS_QMOPT_PQUOTA) && q->qi_pquotaip) {
		xfs_irele(q->qi_pquotaip);
		q->qi_pquotaip = NULL;
	}

out_unlock:
	mutex_unlock(&q->qi_quotaofflock);
	return error;
}