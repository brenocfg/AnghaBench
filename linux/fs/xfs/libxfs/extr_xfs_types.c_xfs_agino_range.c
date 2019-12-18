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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  scalar_t__ xfs_agino_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cluster_align; } ;

/* Variables and functions */
 TYPE_1__* M_IGEO (struct xfs_mount*) ; 
 scalar_t__ XFS_AGB_TO_AGINO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_AGFL_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ag_block_count (struct xfs_mount*,int /*<<< orphan*/ ) ; 

void
xfs_agino_range(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agino_t		*first,
	xfs_agino_t		*last)
{
	xfs_agblock_t		bno;
	xfs_agblock_t		eoag;

	eoag = xfs_ag_block_count(mp, agno);

	/*
	 * Calculate the first inode, which will be in the first
	 * cluster-aligned block after the AGFL.
	 */
	bno = round_up(XFS_AGFL_BLOCK(mp) + 1, M_IGEO(mp)->cluster_align);
	*first = XFS_AGB_TO_AGINO(mp, bno);

	/*
	 * Calculate the last inode, which will be at the end of the
	 * last (aligned) cluster that can be allocated in the AG.
	 */
	bno = round_down(eoag, M_IGEO(mp)->cluster_align);
	*last = XFS_AGB_TO_AGINO(mp, bno) - 1;
}