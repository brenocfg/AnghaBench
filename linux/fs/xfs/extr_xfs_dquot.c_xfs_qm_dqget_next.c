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

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  XFS_IS_DQUOT_UNINITIALIZED (struct xfs_dquot*) ; 
 int xfs_dq_get_next_id (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_qm_dqget (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_dquot**) ; 
 int /*<<< orphan*/  xfs_qm_dqput (struct xfs_dquot*) ; 

int
xfs_qm_dqget_next(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	struct xfs_dquot	**dqpp)
{
	struct xfs_dquot	*dqp;
	int			error = 0;

	*dqpp = NULL;
	for (; !error; error = xfs_dq_get_next_id(mp, type, &id)) {
		error = xfs_qm_dqget(mp, id, type, false, &dqp);
		if (error == -ENOENT)
			continue;
		else if (error != 0)
			break;

		if (!XFS_IS_DQUOT_UNINITIALIZED(dqp)) {
			*dqpp = dqp;
			return 0;
		}

		xfs_qm_dqput(dqp);
	}

	return error;
}