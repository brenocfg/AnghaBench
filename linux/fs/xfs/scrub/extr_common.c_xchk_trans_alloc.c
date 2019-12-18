#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct xfs_scrub {int /*<<< orphan*/  tp; int /*<<< orphan*/  mp; TYPE_1__* sm; } ;
struct TYPE_4__ {int /*<<< orphan*/  tr_itruncate; } ;
struct TYPE_3__ {int sm_flags; } ;

/* Variables and functions */
 TYPE_2__* M_RES (int /*<<< orphan*/ ) ; 
 int XFS_SCRUB_IFLAG_REPAIR ; 
 int xfs_trans_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_trans_alloc_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xchk_trans_alloc(
	struct xfs_scrub	*sc,
	uint			resblks)
{
	if (sc->sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR)
		return xfs_trans_alloc(sc->mp, &M_RES(sc->mp)->tr_itruncate,
				resblks, 0, 0, &sc->tp);

	return xfs_trans_alloc_empty(sc->mp, &sc->tp);
}