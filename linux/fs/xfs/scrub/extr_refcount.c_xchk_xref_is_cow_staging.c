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
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  refc_cur; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  sm; } ;
struct xfs_refcount_irec {int rc_startblock; int rc_refcount; scalar_t__ rc_blockcount; } ;

/* Variables and functions */
 int XFS_REFC_COW_START ; 
 int /*<<< orphan*/  xchk_btree_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ xchk_skip_xref (int /*<<< orphan*/ ) ; 
 int xfs_refcount_get_rec (int /*<<< orphan*/ ,struct xfs_refcount_irec*,int*) ; 
 int xfs_refcount_lookup_le (int /*<<< orphan*/ ,scalar_t__,int*) ; 

void
xchk_xref_is_cow_staging(
	struct xfs_scrub		*sc,
	xfs_agblock_t			agbno,
	xfs_extlen_t			len)
{
	struct xfs_refcount_irec	rc;
	bool				has_cowflag;
	int				has_refcount;
	int				error;

	if (!sc->sa.refc_cur || xchk_skip_xref(sc->sm))
		return;

	/* Find the CoW staging extent. */
	error = xfs_refcount_lookup_le(sc->sa.refc_cur,
			agbno + XFS_REFC_COW_START, &has_refcount);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		return;
	if (!has_refcount) {
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
		return;
	}

	error = xfs_refcount_get_rec(sc->sa.refc_cur, &rc, &has_refcount);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		return;
	if (!has_refcount) {
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
		return;
	}

	/* CoW flag must be set, refcount must be 1. */
	has_cowflag = (rc.rc_startblock & XFS_REFC_COW_START);
	if (!has_cowflag || rc.rc_refcount != 1)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);

	/* Must be at least as long as what was passed in */
	if (rc.rc_blockcount < len)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
}