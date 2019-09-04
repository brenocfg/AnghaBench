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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_blocklog; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  agno; struct xfs_buf* agbp; } ;
struct TYPE_6__ {TYPE_2__ a; } ;
struct xfs_btree_cur {size_t bc_btnum; int bc_flags; TYPE_3__ bc_private; int /*<<< orphan*/  bc_statoff; int /*<<< orphan*/  bc_nlevels; int /*<<< orphan*/ * bc_ops; int /*<<< orphan*/  bc_blocklog; struct xfs_mount* bc_mp; struct xfs_trans* bc_tp; } ;
struct xfs_agf {int /*<<< orphan*/ * agf_levels; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 size_t XFS_BTNUM_RMAP ; 
 int XFS_BTREE_CRC_BLOCKS ; 
 int XFS_BTREE_OVERLAPPING ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_STATS_CALC_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_btree_cur* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_btree_cur_zone ; 
 int /*<<< orphan*/  xfs_rmapbt_ops ; 
 int /*<<< orphan*/  xs_rmap_2 ; 

struct xfs_btree_cur *
xfs_rmapbt_init_cursor(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct xfs_buf		*agbp,
	xfs_agnumber_t		agno)
{
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(agbp);
	struct xfs_btree_cur	*cur;

	cur = kmem_zone_zalloc(xfs_btree_cur_zone, KM_NOFS);
	cur->bc_tp = tp;
	cur->bc_mp = mp;
	/* Overlapping btree; 2 keys per pointer. */
	cur->bc_btnum = XFS_BTNUM_RMAP;
	cur->bc_flags = XFS_BTREE_CRC_BLOCKS | XFS_BTREE_OVERLAPPING;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;
	cur->bc_ops = &xfs_rmapbt_ops;
	cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]);
	cur->bc_statoff = XFS_STATS_CALC_INDEX(xs_rmap_2);

	cur->bc_private.a.agbp = agbp;
	cur->bc_private.a.agno = agno;

	return cur;
}