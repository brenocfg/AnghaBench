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
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct TYPE_2__ {void* sb_fdblocks; void* sb_ifree; void* sb_icount; } ;
struct xfs_mount {TYPE_1__ m_sb; int /*<<< orphan*/  m_fdblocks; int /*<<< orphan*/  m_ifree; int /*<<< orphan*/  m_icount; } ;
struct xfs_dsb {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BLFT_SB_BUF ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 void* percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_to_disk (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 struct xfs_buf* xfs_trans_getsb (struct xfs_trans*,struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ,int) ; 

void
xfs_log_sb(
	struct xfs_trans	*tp)
{
	struct xfs_mount	*mp = tp->t_mountp;
	struct xfs_buf		*bp = xfs_trans_getsb(tp, mp);

	mp->m_sb.sb_icount = percpu_counter_sum(&mp->m_icount);
	mp->m_sb.sb_ifree = percpu_counter_sum(&mp->m_ifree);
	mp->m_sb.sb_fdblocks = percpu_counter_sum(&mp->m_fdblocks);

	xfs_sb_to_disk(XFS_BUF_TO_SBP(bp), &mp->m_sb);
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SB_BUF);
	xfs_trans_log_buf(tp, bp, 0, sizeof(struct xfs_dsb) - 1);
}