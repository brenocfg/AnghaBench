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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  scalar_t__ xfs_agblock_t ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_AGFL_BLOCK (struct xfs_mount*) ; 
 scalar_t__ xfs_ag_block_count (struct xfs_mount*,int /*<<< orphan*/ ) ; 

bool
xfs_verify_agbno(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno)
{
	xfs_agblock_t		eoag;

	eoag = xfs_ag_block_count(mp, agno);
	if (agbno >= eoag)
		return false;
	if (agbno <= XFS_AGFL_BLOCK(mp))
		return false;
	return true;
}