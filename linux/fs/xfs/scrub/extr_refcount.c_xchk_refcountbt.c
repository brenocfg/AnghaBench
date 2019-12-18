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
struct TYPE_2__ {int /*<<< orphan*/  refc_cur; } ;
struct xfs_scrub {TYPE_1__ sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_RMAP_OINFO_REFC ; 
 int xchk_btree (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchk_refcount_xref_rmap (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_refcountbt_rec ; 

int
xchk_refcountbt(
	struct xfs_scrub	*sc)
{
	xfs_agblock_t		cow_blocks = 0;
	int			error;

	error = xchk_btree(sc, sc->sa.refc_cur, xchk_refcountbt_rec,
			&XFS_RMAP_OINFO_REFC, &cow_blocks);
	if (error)
		return error;

	xchk_refcount_xref_rmap(sc, cow_blocks);

	return 0;
}