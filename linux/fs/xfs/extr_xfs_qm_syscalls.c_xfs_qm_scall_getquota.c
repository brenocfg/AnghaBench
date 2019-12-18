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
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_mount {int dummy; } ;
struct xfs_dquot {int dummy; } ;
struct qc_dqblk {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ XFS_IS_DQUOT_UNINITIALIZED (struct xfs_dquot*) ; 
 int xfs_qm_dqget (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_dquot**) ; 
 int /*<<< orphan*/  xfs_qm_dqput (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_qm_scall_getquota_fill_qc (struct xfs_mount*,int /*<<< orphan*/ ,struct xfs_dquot*,struct qc_dqblk*) ; 

int
xfs_qm_scall_getquota(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	struct qc_dqblk		*dst)
{
	struct xfs_dquot	*dqp;
	int			error;

	/*
	 * Try to get the dquot. We don't want it allocated on disk, so don't
	 * set doalloc. If it doesn't exist, we'll get ENOENT back.
	 */
	error = xfs_qm_dqget(mp, id, type, false, &dqp);
	if (error)
		return error;

	/*
	 * If everything's NULL, this dquot doesn't quite exist as far as
	 * our utility programs are concerned.
	 */
	if (XFS_IS_DQUOT_UNINITIALIZED(dqp)) {
		error = -ENOENT;
		goto out_put;
	}

	xfs_qm_scall_getquota_fill_qc(mp, type, dqp, dst);

out_put:
	xfs_qm_dqput(dqp);
	return error;
}