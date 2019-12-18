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
struct xfs_mount {int dummy; } ;
struct xfs_buf_map {int /*<<< orphan*/  bm_len; int /*<<< orphan*/  bm_bn; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; int /*<<< orphan*/  br_blockcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 int ENOMEM ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_FSB_TO_BB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,scalar_t__) ; 
 struct xfs_buf_map* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_buf_map_from_irec(
	struct xfs_mount	*mp,
	struct xfs_buf_map	**mapp,
	int			*nmaps,
	struct xfs_bmbt_irec	*irecs,
	int			nirecs)
{
	struct xfs_buf_map	*map;
	int			i;

	ASSERT(*nmaps == 1);
	ASSERT(nirecs >= 1);

	if (nirecs > 1) {
		map = kmem_zalloc(nirecs * sizeof(struct xfs_buf_map),
				  KM_NOFS);
		if (!map)
			return -ENOMEM;
		*mapp = map;
	}

	*nmaps = nirecs;
	map = *mapp;
	for (i = 0; i < *nmaps; i++) {
		ASSERT(irecs[i].br_startblock != DELAYSTARTBLOCK &&
		       irecs[i].br_startblock != HOLESTARTBLOCK);
		map[i].bm_bn = XFS_FSB_TO_DADDR(mp, irecs[i].br_startblock);
		map[i].bm_len = XFS_FSB_TO_BB(mp, irecs[i].br_blockcount);
	}
	return 0;
}