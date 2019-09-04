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
typedef  int uint64_t ;
struct TYPE_2__ {int sb_imax_pct; int sb_dblocks; int sb_inopblog; } ;
struct xfs_mount {int m_maxicount; int /*<<< orphan*/  m_growlock; int /*<<< orphan*/  m_generation; TYPE_1__ m_sb; } ;
struct xfs_growfs_data {int imaxpct; int newblocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xfs_growfs_data_private (struct xfs_mount*,struct xfs_growfs_data*) ; 
 int xfs_growfs_imaxpct (struct xfs_mount*,int) ; 
 int xfs_update_secondary_sbs (struct xfs_mount*) ; 

int
xfs_growfs_data(
	struct xfs_mount	*mp,
	struct xfs_growfs_data	*in)
{
	int			error = 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (!mutex_trylock(&mp->m_growlock))
		return -EWOULDBLOCK;

	/* update imaxpct separately to the physical grow of the filesystem */
	if (in->imaxpct != mp->m_sb.sb_imax_pct) {
		error = xfs_growfs_imaxpct(mp, in->imaxpct);
		if (error)
			goto out_error;
	}

	if (in->newblocks != mp->m_sb.sb_dblocks) {
		error = xfs_growfs_data_private(mp, in);
		if (error)
			goto out_error;
	}

	/* Post growfs calculations needed to reflect new state in operations */
	if (mp->m_sb.sb_imax_pct) {
		uint64_t icount = mp->m_sb.sb_dblocks * mp->m_sb.sb_imax_pct;
		do_div(icount, 100);
		mp->m_maxicount = icount << mp->m_sb.sb_inopblog;
	} else
		mp->m_maxicount = 0;

	/* Update secondary superblocks now the physical grow has completed */
	error = xfs_update_secondary_sbs(mp);

out_error:
	/*
	 * Increment the generation unconditionally, the error could be from
	 * updating the secondary superblocks, in which case the new size
	 * is live already.
	 */
	mp->m_generation++;
	mutex_unlock(&mp->m_growlock);
	return error;
}