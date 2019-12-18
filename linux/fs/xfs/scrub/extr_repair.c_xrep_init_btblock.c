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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_btnum_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  agno; } ;
struct xfs_scrub {TYPE_1__ sa; struct xfs_mount* mp; struct xfs_trans* tp; } ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf {struct xfs_buf_ops const* b_ops; int /*<<< orphan*/  b_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BBTOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BLFT_BTREE_BUF ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xrep_init_btblock (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_btree_init_block (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_zero (struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 struct xfs_buf* xfs_trans_get_buf (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 

int
xrep_init_btblock(
	struct xfs_scrub		*sc,
	xfs_fsblock_t			fsb,
	struct xfs_buf			**bpp,
	xfs_btnum_t			btnum,
	const struct xfs_buf_ops	*ops)
{
	struct xfs_trans		*tp = sc->tp;
	struct xfs_mount		*mp = sc->mp;
	struct xfs_buf			*bp;

	trace_xrep_init_btblock(mp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), btnum);

	ASSERT(XFS_FSB_TO_AGNO(mp, fsb) == sc->sa.agno);
	bp = xfs_trans_get_buf(tp, mp->m_ddev_targp, XFS_FSB_TO_DADDR(mp, fsb),
			XFS_FSB_TO_BB(mp, 1), 0);
	xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
	xfs_btree_init_block(mp, bp, btnum, 0, 0, sc->sa.agno);
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_BTREE_BUF);
	xfs_trans_log_buf(tp, bp, 0, BBTOB(bp->b_length) - 1);
	bp->b_ops = ops;
	*bpp = bp;

	return 0;
}