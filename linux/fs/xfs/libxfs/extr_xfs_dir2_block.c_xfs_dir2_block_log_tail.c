#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* t_mountp; } ;
typedef  TYPE_2__ xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  m_dir_geo; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (TYPE_2__*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_block_log_tail(
	xfs_trans_t		*tp,		/* transaction structure */
	struct xfs_buf		*bp)		/* block buffer */
{
	xfs_dir2_data_hdr_t	*hdr = bp->b_addr;
	xfs_dir2_block_tail_t	*btp;

	btp = xfs_dir2_block_tail_p(tp->t_mountp->m_dir_geo, hdr);
	xfs_trans_log_buf(tp, bp, (uint)((char *)btp - (char *)hdr),
		(uint)((char *)(btp + 1) - (char *)hdr - 1));
}