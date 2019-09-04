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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  refc_cur; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  xchk_btree_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ xchk_skip_xref (int /*<<< orphan*/ ) ; 
 int xfs_refcount_has_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
xchk_xref_is_not_shared(
	struct xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
{
	bool			shared;
	int			error;

	if (!sc->sa.refc_cur || xchk_skip_xref(sc->sm))
		return;

	error = xfs_refcount_has_record(sc->sa.refc_cur, agbno, len, &shared);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		return;
	if (shared)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
}