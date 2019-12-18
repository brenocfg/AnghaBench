#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 scalar_t__ XFS_ALLOC_AGFL_RESERVE ; 
 unsigned int XFS_BB_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 scalar_t__ xfs_sb_version_hasfinobt (TYPE_1__*) ; 
 scalar_t__ xfs_sb_version_hasreflink (TYPE_1__*) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (TYPE_1__*) ; 

unsigned int
xfs_alloc_ag_max_usable(
	struct xfs_mount	*mp)
{
	unsigned int		blocks;

	blocks = XFS_BB_TO_FSB(mp, XFS_FSS_TO_BB(mp, 4)); /* ag headers */
	blocks += XFS_ALLOC_AGFL_RESERVE;
	blocks += 3;			/* AGF, AGI btree root blocks */
	if (xfs_sb_version_hasfinobt(&mp->m_sb))
		blocks++;		/* finobt root block */
	if (xfs_sb_version_hasrmapbt(&mp->m_sb))
		blocks++; 		/* rmap root block */
	if (xfs_sb_version_hasreflink(&mp->m_sb))
		blocks++;		/* refcount root block */

	return mp->m_sb.sb_agblocks - blocks;
}