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
struct xfs_mount {int /*<<< orphan*/  m_ail; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 int /*<<< orphan*/  xfs_ail_push_all_sync (int /*<<< orphan*/ ) ; 
 int xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 

int
xchk_checkpoint_log(
	struct xfs_mount	*mp)
{
	int			error;

	error = xfs_log_force(mp, XFS_LOG_SYNC);
	if (error)
		return error;
	xfs_ail_push_all_sync(mp->m_ail);
	return 0;
}