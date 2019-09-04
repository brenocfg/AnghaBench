#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xfs_btnum_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sb_blocklog; } ;
struct xfs_mount {TYPE_3__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  agno; struct xfs_buf* agbp; } ;
struct TYPE_5__ {TYPE_1__ a; } ;
struct xfs_btree_cur {size_t bc_btnum; int /*<<< orphan*/  bc_flags; TYPE_2__ bc_private; void* bc_nlevels; int /*<<< orphan*/ * bc_ops; void* bc_statoff; int /*<<< orphan*/  bc_blocklog; struct xfs_mount* bc_mp; struct xfs_trans* bc_tp; } ;
struct xfs_agf {int /*<<< orphan*/ * agf_levels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 size_t XFS_BTNUM_BNO ; 
 size_t XFS_BTNUM_CNT ; 
 int /*<<< orphan*/  XFS_BTREE_CRC_BLOCKS ; 
 int /*<<< orphan*/  XFS_BTREE_LASTREC_UPDATE ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 void* XFS_STATS_CALC_INDEX (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_btree_cur* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bnobt_ops ; 
 int /*<<< orphan*/  xfs_btree_cur_zone ; 
 int /*<<< orphan*/  xfs_cntbt_ops ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_3__*) ; 
 int /*<<< orphan*/  xs_abtb_2 ; 
 int /*<<< orphan*/  xs_abtc_2 ; 

struct xfs_btree_cur *			/* new alloc btree cursor */
xfs_allocbt_init_cursor(
	struct xfs_mount	*mp,		/* file system mount point */
	struct xfs_trans	*tp,		/* transaction pointer */
	struct xfs_buf		*agbp,		/* buffer for agf structure */
	xfs_agnumber_t		agno,		/* allocation group number */
	xfs_btnum_t		btnum)		/* btree identifier */
{
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(agbp);
	struct xfs_btree_cur	*cur;

	ASSERT(btnum == XFS_BTNUM_BNO || btnum == XFS_BTNUM_CNT);

	cur = kmem_zone_zalloc(xfs_btree_cur_zone, KM_NOFS);

	cur->bc_tp = tp;
	cur->bc_mp = mp;
	cur->bc_btnum = btnum;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;

	if (btnum == XFS_BTNUM_CNT) {
		cur->bc_statoff = XFS_STATS_CALC_INDEX(xs_abtc_2);
		cur->bc_ops = &xfs_cntbt_ops;
		cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]);
		cur->bc_flags = XFS_BTREE_LASTREC_UPDATE;
	} else {
		cur->bc_statoff = XFS_STATS_CALC_INDEX(xs_abtb_2);
		cur->bc_ops = &xfs_bnobt_ops;
		cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]);
	}

	cur->bc_private.a.agbp = agbp;
	cur->bc_private.a.agno = agno;

	if (xfs_sb_version_hascrc(&mp->m_sb))
		cur->bc_flags |= XFS_BTREE_CRC_BLOCKS;

	return cur;
}