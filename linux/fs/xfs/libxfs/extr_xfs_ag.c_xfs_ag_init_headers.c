#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sb_blocksize; } ;
struct xfs_mount {scalar_t__ m_ag_prealloc_blocks; TYPE_1__ m_sb; } ;
struct xfs_aghdr_grow_data {scalar_t__ daddr; int need_init; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * work; int /*<<< orphan*/  type; int /*<<< orphan*/  numblks; } ;
struct aghdr_init_data {scalar_t__ daddr; int /*<<< orphan*/  type; int /*<<< orphan*/  numblks; scalar_t__ agsize; int /*<<< orphan*/  nfree; int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTOBB (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_AGB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_AGFL_DADDR (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_AGF_DADDR (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_AGI_DADDR (struct xfs_mount*) ; 
 scalar_t__ XFS_AG_DADDR (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BNO_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_BTNUM_FINO ; 
 int /*<<< orphan*/  XFS_BTNUM_INO ; 
 int /*<<< orphan*/  XFS_BTNUM_REFC ; 
 scalar_t__ XFS_BUF_DADDR_NULL ; 
 int /*<<< orphan*/  XFS_CNT_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_FIBT_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_IBT_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_RMAP_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_SB_DADDR ; 
 int xfs_ag_init_hdr (struct xfs_mount*,struct aghdr_init_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_agf_buf_ops ; 
 int /*<<< orphan*/  xfs_agfblock_init ; 
 int /*<<< orphan*/  xfs_agfl_buf_ops ; 
 int /*<<< orphan*/  xfs_agflblock_init ; 
 int /*<<< orphan*/  xfs_agi_buf_ops ; 
 int /*<<< orphan*/  xfs_agiblock_init ; 
 int /*<<< orphan*/  xfs_bnobt_buf_ops ; 
 int /*<<< orphan*/  xfs_bnoroot_init ; 
 int /*<<< orphan*/  xfs_btroot_init ; 
 int /*<<< orphan*/  xfs_cntbt_buf_ops ; 
 int /*<<< orphan*/  xfs_cntroot_init ; 
 int /*<<< orphan*/  xfs_finobt_buf_ops ; 
 int /*<<< orphan*/  xfs_inobt_buf_ops ; 
 int /*<<< orphan*/  xfs_refc_block (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_refcountbt_buf_ops ; 
 int /*<<< orphan*/  xfs_rmapbt_buf_ops ; 
 int /*<<< orphan*/  xfs_rmaproot_init ; 
 int /*<<< orphan*/  xfs_sb_buf_ops ; 
 int xfs_sb_version_hasfinobt (TYPE_1__*) ; 
 int xfs_sb_version_hasreflink (TYPE_1__*) ; 
 int xfs_sb_version_hasrmapbt (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_sbblock_init ; 

int
xfs_ag_init_headers(
	struct xfs_mount	*mp,
	struct aghdr_init_data	*id)

{
	struct xfs_aghdr_grow_data aghdr_data[] = {
	{ /* SB */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_SB_DADDR),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_sb_buf_ops,
		.work = &xfs_sbblock_init,
		.need_init = true
	},
	{ /* AGF */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGF_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agf_buf_ops,
		.work = &xfs_agfblock_init,
		.need_init = true
	},
	{ /* AGFL */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGFL_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agfl_buf_ops,
		.work = &xfs_agflblock_init,
		.need_init = true
	},
	{ /* AGI */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGI_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agi_buf_ops,
		.work = &xfs_agiblock_init,
		.need_init = true
	},
	{ /* BNO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_BNO_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_bnobt_buf_ops,
		.work = &xfs_bnoroot_init,
		.need_init = true
	},
	{ /* CNT root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_CNT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_cntbt_buf_ops,
		.work = &xfs_cntroot_init,
		.need_init = true
	},
	{ /* INO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_IBT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_inobt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_INO,
		.need_init = true
	},
	{ /* FINO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_FIBT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_finobt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_FINO,
		.need_init =  xfs_sb_version_hasfinobt(&mp->m_sb)
	},
	{ /* RMAP root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_RMAP_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_rmapbt_buf_ops,
		.work = &xfs_rmaproot_init,
		.need_init = xfs_sb_version_hasrmapbt(&mp->m_sb)
	},
	{ /* REFC root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, xfs_refc_block(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_refcountbt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_REFC,
		.need_init = xfs_sb_version_hasreflink(&mp->m_sb)
	},
	{ /* NULL terminating block */
		.daddr = XFS_BUF_DADDR_NULL,
	}
	};
	struct  xfs_aghdr_grow_data *dp;
	int			error = 0;

	/* Account for AG free space in new AG */
	id->nfree += id->agsize - mp->m_ag_prealloc_blocks;
	for (dp = &aghdr_data[0]; dp->daddr != XFS_BUF_DADDR_NULL; dp++) {
		if (!dp->need_init)
			continue;

		id->daddr = dp->daddr;
		id->numblks = dp->numblks;
		id->type = dp->type;
		error = xfs_ag_init_hdr(mp, id, dp->work, dp->ops);
		if (error)
			break;
	}
	return error;
}