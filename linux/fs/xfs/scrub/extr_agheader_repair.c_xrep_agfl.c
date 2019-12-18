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
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_2__ {struct xfs_buf* agfl_bp; struct xfs_buf* agf_bp; int /*<<< orphan*/  agno; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  tp; struct xfs_mount* mp; } ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; int /*<<< orphan*/  m_sb; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; } ;
struct xfs_bitmap {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XFS_AGFL_DADDR (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_AG_DADDR (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_AG_RESV_AGFL ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_RMAP_OINFO_AG ; 
 int /*<<< orphan*/  xchk_perag_get (struct xfs_mount*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_agfl_buf_ops ; 
 int xfs_alloc_read_agf (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_bitmap_destroy (struct xfs_bitmap*) ; 
 int /*<<< orphan*/  xfs_bitmap_init (struct xfs_bitmap*) ; 
 int /*<<< orphan*/  xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 
 int xfs_trans_read_buf (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ *) ; 
 int xrep_agfl_collect_blocks (struct xfs_scrub*,struct xfs_buf*,struct xfs_bitmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xrep_agfl_init_header (struct xfs_scrub*,struct xfs_buf*,struct xfs_bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xrep_agfl_update_agf (struct xfs_scrub*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xrep_reap_extents (struct xfs_scrub*,struct xfs_bitmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xrep_roll_ag_trans (struct xfs_scrub*) ; 

int
xrep_agfl(
	struct xfs_scrub	*sc)
{
	struct xfs_bitmap	agfl_extents;
	struct xfs_mount	*mp = sc->mp;
	struct xfs_buf		*agf_bp;
	struct xfs_buf		*agfl_bp;
	xfs_agblock_t		flcount;
	int			error;

	/* We require the rmapbt to rebuild anything. */
	if (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		return -EOPNOTSUPP;

	xchk_perag_get(sc->mp, &sc->sa);
	xfs_bitmap_init(&agfl_extents);

	/*
	 * Read the AGF so that we can query the rmapbt.  We hope that there's
	 * nothing wrong with the AGF, but all the AG header repair functions
	 * have this chicken-and-egg problem.
	 */
	error = xfs_alloc_read_agf(mp, sc->tp, sc->sa.agno, 0, &agf_bp);
	if (error)
		return error;
	if (!agf_bp)
		return -ENOMEM;

	/*
	 * Make sure we have the AGFL buffer, as scrub might have decided it
	 * was corrupt after xfs_alloc_read_agfl failed with -EFSCORRUPTED.
	 */
	error = xfs_trans_read_buf(mp, sc->tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, sc->sa.agno, XFS_AGFL_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agfl_bp, NULL);
	if (error)
		return error;
	agfl_bp->b_ops = &xfs_agfl_buf_ops;

	/* Gather all the extents we're going to put on the new AGFL. */
	error = xrep_agfl_collect_blocks(sc, agf_bp, &agfl_extents, &flcount);
	if (error)
		goto err;

	/*
	 * Update AGF and AGFL.  We reset the global free block counter when
	 * we adjust the AGF flcount (which can fail) so avoid updating any
	 * buffers until we know that part works.
	 */
	xrep_agfl_update_agf(sc, agf_bp, flcount);
	xrep_agfl_init_header(sc, agfl_bp, &agfl_extents, flcount);

	/*
	 * Ok, the AGFL should be ready to go now.  Roll the transaction to
	 * make the new AGFL permanent before we start using it to return
	 * freespace overflow to the freespace btrees.
	 */
	sc->sa.agf_bp = agf_bp;
	sc->sa.agfl_bp = agfl_bp;
	error = xrep_roll_ag_trans(sc);
	if (error)
		goto err;

	/* Dump any AGFL overflow. */
	return xrep_reap_extents(sc, &agfl_extents, &XFS_RMAP_OINFO_AG,
			XFS_AG_RESV_AGFL);
err:
	xfs_bitmap_destroy(&agfl_extents);
	return error;
}