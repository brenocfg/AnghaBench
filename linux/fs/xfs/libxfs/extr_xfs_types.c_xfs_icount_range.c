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
typedef  scalar_t__ xfs_agino_t ;
struct TYPE_2__ {scalar_t__ sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 unsigned long long XFS_INODES_PER_CHUNK ; 
 int /*<<< orphan*/  xfs_agino_range (struct xfs_mount*,scalar_t__,scalar_t__*,scalar_t__*) ; 

void
xfs_icount_range(
	struct xfs_mount	*mp,
	unsigned long long	*min,
	unsigned long long	*max)
{
	unsigned long long	nr_inos = 0;
	xfs_agnumber_t		agno;

	/* root, rtbitmap, rtsum all live in the first chunk */
	*min = XFS_INODES_PER_CHUNK;

	for (agno = 0; agno < mp->m_sb.sb_agcount; agno++) {
		xfs_agino_t	first, last;

		xfs_agino_range(mp, agno, &first, &last);
		nr_inos += last - first + 1;
	}
	*max = nr_inos;
}