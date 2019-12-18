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
struct xfs_scrub {int /*<<< orphan*/  sick_mask; int /*<<< orphan*/  mp; int /*<<< orphan*/  ip; TYPE_1__* sm; } ;
struct xfs_perag {int dummy; } ;
struct TYPE_4__ {int group; } ;
struct TYPE_3__ {int sm_flags; size_t sm_type; int /*<<< orphan*/  sm_agno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
#define  XHG_AG 131 
#define  XHG_FS 130 
#define  XHG_INO 129 
#define  XHG_RT 128 
 TYPE_2__* type_to_health_flag ; 
 int /*<<< orphan*/  xfs_ag_mark_healthy (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ag_mark_sick (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fs_mark_healthy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fs_mark_sick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_mark_healthy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_mark_sick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_perag* xfs_perag_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int /*<<< orphan*/  xfs_rt_mark_healthy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_rt_mark_sick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xchk_update_health(
	struct xfs_scrub	*sc)
{
	struct xfs_perag	*pag;
	bool			bad;

	if (!sc->sick_mask)
		return;

	bad = (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT);
	switch (type_to_health_flag[sc->sm->sm_type].group) {
	case XHG_AG:
		pag = xfs_perag_get(sc->mp, sc->sm->sm_agno);
		if (bad)
			xfs_ag_mark_sick(pag, sc->sick_mask);
		else
			xfs_ag_mark_healthy(pag, sc->sick_mask);
		xfs_perag_put(pag);
		break;
	case XHG_INO:
		if (!sc->ip)
			return;
		if (bad)
			xfs_inode_mark_sick(sc->ip, sc->sick_mask);
		else
			xfs_inode_mark_healthy(sc->ip, sc->sick_mask);
		break;
	case XHG_FS:
		if (bad)
			xfs_fs_mark_sick(sc->mp, sc->sick_mask);
		else
			xfs_fs_mark_healthy(sc->mp, sc->sick_mask);
		break;
	case XHG_RT:
		if (bad)
			xfs_rt_mark_sick(sc->mp, sc->sick_mask);
		else
			xfs_rt_mark_healthy(sc->mp, sc->sick_mask);
		break;
	default:
		ASSERT(0);
		break;
	}
}