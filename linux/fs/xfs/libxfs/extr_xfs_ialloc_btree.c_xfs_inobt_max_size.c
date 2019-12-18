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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  scalar_t__ xfs_agnumber_t ;
typedef  scalar_t__ xfs_agblock_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int sb_inopblock; scalar_t__ sb_logblocks; scalar_t__ sb_logstart; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct TYPE_4__ {scalar_t__* inobt_mxr; int /*<<< orphan*/  inobt_mnr; } ;

/* Variables and functions */
 TYPE_2__* M_IGEO (struct xfs_mount*) ; 
 scalar_t__ XFS_FSB_TO_AGNO (struct xfs_mount*,scalar_t__) ; 
 int XFS_INODES_PER_CHUNK ; 
 scalar_t__ xfs_ag_block_count (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_btree_calc_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static xfs_extlen_t
xfs_inobt_max_size(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno)
{
	xfs_agblock_t		agblocks = xfs_ag_block_count(mp, agno);

	/* Bail out if we're uninitialized, which can happen in mkfs. */
	if (M_IGEO(mp)->inobt_mxr[0] == 0)
		return 0;

	/*
	 * The log is permanently allocated, so the space it occupies will
	 * never be available for the kinds of things that would require btree
	 * expansion.  We therefore can pretend the space isn't there.
	 */
	if (mp->m_sb.sb_logstart &&
	    XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart) == agno)
		agblocks -= mp->m_sb.sb_logblocks;

	return xfs_btree_calc_size(M_IGEO(mp)->inobt_mnr,
				(uint64_t)agblocks * mp->m_sb.sb_inopblock /
					XFS_INODES_PER_CHUNK);
}