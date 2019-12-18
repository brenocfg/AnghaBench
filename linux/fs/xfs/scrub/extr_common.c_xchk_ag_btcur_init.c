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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_scrub {int /*<<< orphan*/  tp; struct xfs_mount* mp; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xchk_ag {int /*<<< orphan*/  refc_cur; int /*<<< orphan*/  agf_bp; int /*<<< orphan*/  pag; int /*<<< orphan*/  rmap_cur; void* fino_cur; int /*<<< orphan*/  agi_bp; void* ino_cur; void* cnt_cur; void* bno_cur; int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  XFS_BTNUM_BNO ; 
 int /*<<< orphan*/  XFS_BTNUM_CNT ; 
 int /*<<< orphan*/  XFS_BTNUM_FINO ; 
 int /*<<< orphan*/  XFS_BTNUM_INO ; 
 int /*<<< orphan*/  XFS_BTNUM_REFC ; 
 int /*<<< orphan*/  XFS_BTNUM_RMAP ; 
 scalar_t__ xchk_ag_btree_healthy_enough (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_perag_get (struct xfs_mount*,struct xchk_ag*) ; 
 void* xfs_allocbt_init_cursor (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xfs_inobt_init_cursor (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_refcountbt_init_cursor (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_rmapbt_init_cursor (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hasfinobt (int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_sb_version_hasreflink (int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

int
xchk_ag_btcur_init(
	struct xfs_scrub	*sc,
	struct xchk_ag		*sa)
{
	struct xfs_mount	*mp = sc->mp;
	xfs_agnumber_t		agno = sa->agno;

	xchk_perag_get(sc->mp, sa);
	if (sa->agf_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_BNO)) {
		/* Set up a bnobt cursor for cross-referencing. */
		sa->bno_cur = xfs_allocbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno, XFS_BTNUM_BNO);
		if (!sa->bno_cur)
			goto err;
	}

	if (sa->agf_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_CNT)) {
		/* Set up a cntbt cursor for cross-referencing. */
		sa->cnt_cur = xfs_allocbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno, XFS_BTNUM_CNT);
		if (!sa->cnt_cur)
			goto err;
	}

	/* Set up a inobt cursor for cross-referencing. */
	if (sa->agi_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_INO)) {
		sa->ino_cur = xfs_inobt_init_cursor(mp, sc->tp, sa->agi_bp,
					agno, XFS_BTNUM_INO);
		if (!sa->ino_cur)
			goto err;
	}

	/* Set up a finobt cursor for cross-referencing. */
	if (sa->agi_bp && xfs_sb_version_hasfinobt(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_FINO)) {
		sa->fino_cur = xfs_inobt_init_cursor(mp, sc->tp, sa->agi_bp,
				agno, XFS_BTNUM_FINO);
		if (!sa->fino_cur)
			goto err;
	}

	/* Set up a rmapbt cursor for cross-referencing. */
	if (sa->agf_bp && xfs_sb_version_hasrmapbt(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_RMAP)) {
		sa->rmap_cur = xfs_rmapbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno);
		if (!sa->rmap_cur)
			goto err;
	}

	/* Set up a refcountbt cursor for cross-referencing. */
	if (sa->agf_bp && xfs_sb_version_hasreflink(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_REFC)) {
		sa->refc_cur = xfs_refcountbt_init_cursor(mp, sc->tp,
				sa->agf_bp, agno);
		if (!sa->refc_cur)
			goto err;
	}

	return 0;
err:
	return -ENOMEM;
}