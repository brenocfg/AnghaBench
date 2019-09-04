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
typedef  int uint ;
struct xfs_scrub {int /*<<< orphan*/  tp; TYPE_2__* mp; } ;
struct TYPE_3__ {int sb_qflags; } ;
struct TYPE_4__ {int m_qflags; int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_sb (int /*<<< orphan*/ ) ; 
 int xfs_quota_chkd_flag (int) ; 

void
xrep_force_quotacheck(
	struct xfs_scrub	*sc,
	uint			dqtype)
{
	uint			flag;

	flag = xfs_quota_chkd_flag(dqtype);
	if (!(flag & sc->mp->m_qflags))
		return;

	sc->mp->m_qflags &= ~flag;
	spin_lock(&sc->mp->m_sb_lock);
	sc->mp->m_sb.sb_qflags &= ~flag;
	spin_unlock(&sc->mp->m_sb_lock);
	xfs_log_sb(sc->tp);
}