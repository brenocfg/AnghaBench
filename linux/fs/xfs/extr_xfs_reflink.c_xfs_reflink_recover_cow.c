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
typedef  scalar_t__ xfs_agnumber_t ;
struct TYPE_2__ {scalar_t__ sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 int xfs_refcount_recover_cow_leftovers (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_sb_version_hasreflink (TYPE_1__*) ; 

int
xfs_reflink_recover_cow(
	struct xfs_mount	*mp)
{
	xfs_agnumber_t		agno;
	int			error = 0;

	if (!xfs_sb_version_hasreflink(&mp->m_sb))
		return 0;

	for (agno = 0; agno < mp->m_sb.sb_agcount; agno++) {
		error = xfs_refcount_recover_cow_leftovers(mp, agno);
		if (error)
			break;
	}

	return error;
}