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
typedef  scalar_t__ xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_disk_dquot_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; int /*<<< orphan*/  m_ail; TYPE_1__* m_quotainfo; int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_log_item {int /*<<< orphan*/  li_lsn; } ;
struct TYPE_4__ {struct xfs_log_item qli_item; int /*<<< orphan*/  qli_flush_lsn; } ;
struct xfs_dquot {int q_bufoffset; TYPE_2__ q_logitem; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  q_core; int /*<<< orphan*/  q_blkno; int /*<<< orphan*/  q_flush; struct xfs_mount* q_mount; } ;
struct xfs_disk_dquot {int /*<<< orphan*/  d_id; } ;
struct xfs_dqblk {int /*<<< orphan*/  dd_lsn; struct xfs_disk_dquot dd_diskdq; } ;
struct xfs_buf {struct xfs_dqblk* b_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  qi_dqchunklen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int /*<<< orphan*/  XFS_DQUOT_CRC_OFF ; 
 int /*<<< orphan*/  XFS_DQ_DIRTY ; 
 int XFS_DQ_IS_LOCKED (struct xfs_dquot*) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfs_disk_dquot*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_xfs_dqflush (struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqflush_done (struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqflush_force (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_alert (struct xfs_mount*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_buf_attach_iodone (struct xfs_buf*,int /*<<< orphan*/ ,struct xfs_log_item*) ; 
 scalar_t__ xfs_buf_ispinned (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 scalar_t__ xfs_dqblk_verify (struct xfs_mount*,struct xfs_dqblk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dqfunlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dquot_buf_ops ; 
 int /*<<< orphan*/  xfs_force_shutdown (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_dqflush_done ; 
 int /*<<< orphan*/  xfs_qm_dqunpin_wait (struct xfs_dquot*) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ail_copy_lsn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ail_remove (struct xfs_log_item*,int /*<<< orphan*/ ) ; 
 int xfs_trans_read_buf (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_update_cksum (char*,int,int /*<<< orphan*/ ) ; 

int
xfs_qm_dqflush(
	struct xfs_dquot	*dqp,
	struct xfs_buf		**bpp)
{
	struct xfs_mount	*mp = dqp->q_mount;
	struct xfs_buf		*bp;
	struct xfs_dqblk	*dqb;
	struct xfs_disk_dquot	*ddqp;
	xfs_failaddr_t		fa;
	int			error;

	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	ASSERT(!completion_done(&dqp->q_flush));

	trace_xfs_dqflush(dqp);

	*bpp = NULL;

	xfs_qm_dqunpin_wait(dqp);

	/*
	 * This may have been unpinned because the filesystem is shutting
	 * down forcibly. If that's the case we must not write this dquot
	 * to disk, because the log record didn't make it to disk.
	 *
	 * We also have to remove the log item from the AIL in this case,
	 * as we wait for an emptry AIL as part of the unmount process.
	 */
	if (XFS_FORCED_SHUTDOWN(mp)) {
		struct xfs_log_item	*lip = &dqp->q_logitem.qli_item;
		dqp->dq_flags &= ~XFS_DQ_DIRTY;

		xfs_trans_ail_remove(lip, SHUTDOWN_CORRUPT_INCORE);

		error = -EIO;
		goto out_unlock;
	}

	/*
	 * Get the buffer containing the on-disk dquot
	 */
	error = xfs_trans_read_buf(mp, NULL, mp->m_ddev_targp, dqp->q_blkno,
				   mp->m_quotainfo->qi_dqchunklen, 0, &bp,
				   &xfs_dquot_buf_ops);
	if (error)
		goto out_unlock;

	/*
	 * Calculate the location of the dquot inside the buffer.
	 */
	dqb = bp->b_addr + dqp->q_bufoffset;
	ddqp = &dqb->dd_diskdq;

	/*
	 * A simple sanity check in case we got a corrupted dquot.
	 */
	fa = xfs_dqblk_verify(mp, dqb, be32_to_cpu(ddqp->d_id), 0);
	if (fa) {
		xfs_alert(mp, "corrupt dquot ID 0x%x in memory at %pS",
				be32_to_cpu(ddqp->d_id), fa);
		xfs_buf_relse(bp);
		xfs_dqfunlock(dqp);
		xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
		return -EIO;
	}

	/* This is the only portion of data that needs to persist */
	memcpy(ddqp, &dqp->q_core, sizeof(xfs_disk_dquot_t));

	/*
	 * Clear the dirty field and remember the flush lsn for later use.
	 */
	dqp->dq_flags &= ~XFS_DQ_DIRTY;

	xfs_trans_ail_copy_lsn(mp->m_ail, &dqp->q_logitem.qli_flush_lsn,
					&dqp->q_logitem.qli_item.li_lsn);

	/*
	 * copy the lsn into the on-disk dquot now while we have the in memory
	 * dquot here. This can't be done later in the write verifier as we
	 * can't get access to the log item at that point in time.
	 *
	 * We also calculate the CRC here so that the on-disk dquot in the
	 * buffer always has a valid CRC. This ensures there is no possibility
	 * of a dquot without an up-to-date CRC getting to disk.
	 */
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		dqb->dd_lsn = cpu_to_be64(dqp->q_logitem.qli_item.li_lsn);
		xfs_update_cksum((char *)dqb, sizeof(struct xfs_dqblk),
				 XFS_DQUOT_CRC_OFF);
	}

	/*
	 * Attach an iodone routine so that we can remove this dquot from the
	 * AIL and release the flush lock once the dquot is synced to disk.
	 */
	xfs_buf_attach_iodone(bp, xfs_qm_dqflush_done,
				  &dqp->q_logitem.qli_item);

	/*
	 * If the buffer is pinned then push on the log so we won't
	 * get stuck waiting in the write for too long.
	 */
	if (xfs_buf_ispinned(bp)) {
		trace_xfs_dqflush_force(dqp);
		xfs_log_force(mp, 0);
	}

	trace_xfs_dqflush_done(dqp);
	*bpp = bp;
	return 0;

out_unlock:
	xfs_dqfunlock(dqp);
	return -EIO;
}