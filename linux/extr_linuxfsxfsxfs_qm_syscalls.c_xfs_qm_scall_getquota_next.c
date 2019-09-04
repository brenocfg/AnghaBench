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
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_id; } ;
struct xfs_dquot {TYPE_1__ q_core; } ;
struct qc_dqblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_qm_dqget_next (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_dquot**) ; 
 int /*<<< orphan*/  xfs_qm_dqput (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_qm_scall_getquota_fill_qc (struct xfs_mount*,int /*<<< orphan*/ ,struct xfs_dquot*,struct qc_dqblk*) ; 

int
xfs_qm_scall_getquota_next(
	struct xfs_mount	*mp,
	xfs_dqid_t		*id,
	uint			type,
	struct qc_dqblk		*dst)
{
	struct xfs_dquot	*dqp;
	int			error;

	error = xfs_qm_dqget_next(mp, *id, type, &dqp);
	if (error)
		return error;

	/* Fill in the ID we actually read from disk */
	*id = be32_to_cpu(dqp->q_core.d_id);

	xfs_qm_scall_getquota_fill_qc(mp, type, dqp, dst);

	xfs_qm_dqput(dqp);
	return error;
}