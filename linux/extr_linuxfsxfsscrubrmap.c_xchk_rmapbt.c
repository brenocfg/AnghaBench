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
struct TYPE_2__ {int /*<<< orphan*/  rmap_cur; } ;
struct xfs_scrub {TYPE_1__ sa; } ;
struct xfs_owner_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_RMAP_OWN_AG ; 
 int xchk_btree (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_owner_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchk_rmapbt_rec ; 
 int /*<<< orphan*/  xfs_rmap_ag_owner (struct xfs_owner_info*,int /*<<< orphan*/ ) ; 

int
xchk_rmapbt(
	struct xfs_scrub	*sc)
{
	struct xfs_owner_info	oinfo;

	xfs_rmap_ag_owner(&oinfo, XFS_RMAP_OWN_AG);
	return xchk_btree(sc, sc->sa.rmap_cur, xchk_rmapbt_rec,
			&oinfo, NULL);
}