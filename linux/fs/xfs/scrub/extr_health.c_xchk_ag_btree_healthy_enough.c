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
typedef  int xfs_btnum_t ;
struct xfs_scrub {TYPE_1__* sm; } ;
struct xfs_perag {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sm_flags; int /*<<< orphan*/  sm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_BTNUM_BNO 133 
#define  XFS_BTNUM_CNT 132 
#define  XFS_BTNUM_FINO 131 
#define  XFS_BTNUM_INO 130 
#define  XFS_BTNUM_REFC 129 
#define  XFS_BTNUM_RMAP 128 
 int /*<<< orphan*/  XFS_SCRUB_OFLAG_XFAIL ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_BNOBT ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_CNTBT ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_FINOBT ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_INOBT ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_REFCNTBT ; 
 int /*<<< orphan*/  XFS_SCRUB_TYPE_RMAPBT ; 
 unsigned int XFS_SICK_AG_BNOBT ; 
 unsigned int XFS_SICK_AG_CNTBT ; 
 unsigned int XFS_SICK_AG_FINOBT ; 
 unsigned int XFS_SICK_AG_INOBT ; 
 unsigned int XFS_SICK_AG_REFCNTBT ; 
 unsigned int XFS_SICK_AG_RMAPBT ; 
 scalar_t__ xfs_ag_has_sickness (struct xfs_perag*,unsigned int) ; 

bool
xchk_ag_btree_healthy_enough(
	struct xfs_scrub	*sc,
	struct xfs_perag	*pag,
	xfs_btnum_t		btnum)
{
	unsigned int		mask = 0;

	/*
	 * We always want the cursor if it's the same type as whatever we're
	 * scrubbing, even if we already know the structure is corrupt.
	 *
	 * Otherwise, we're only interested in the btree for cross-referencing.
	 * If we know the btree is bad then don't bother, just set XFAIL.
	 */
	switch (btnum) {
	case XFS_BTNUM_BNO:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_BNOBT)
			return true;
		mask = XFS_SICK_AG_BNOBT;
		break;
	case XFS_BTNUM_CNT:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_CNTBT)
			return true;
		mask = XFS_SICK_AG_CNTBT;
		break;
	case XFS_BTNUM_INO:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_INOBT)
			return true;
		mask = XFS_SICK_AG_INOBT;
		break;
	case XFS_BTNUM_FINO:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_FINOBT)
			return true;
		mask = XFS_SICK_AG_FINOBT;
		break;
	case XFS_BTNUM_RMAP:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_RMAPBT)
			return true;
		mask = XFS_SICK_AG_RMAPBT;
		break;
	case XFS_BTNUM_REFC:
		if (sc->sm->sm_type == XFS_SCRUB_TYPE_REFCNTBT)
			return true;
		mask = XFS_SICK_AG_REFCNTBT;
		break;
	default:
		ASSERT(0);
		return true;
	}

	if (xfs_ag_has_sickness(pag, mask)) {
		sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XFAIL;
		return false;
	}

	return true;
}