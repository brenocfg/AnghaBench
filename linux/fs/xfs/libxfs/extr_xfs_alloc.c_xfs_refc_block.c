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
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 unsigned int XFS_FIBT_BLOCK (struct xfs_mount*) ; 
 unsigned int XFS_IBT_BLOCK (struct xfs_mount*) ; 
 unsigned int XFS_RMAP_BLOCK (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hasfinobt (int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

unsigned int
xfs_refc_block(
	struct xfs_mount	*mp)
{
	if (xfs_sb_version_hasrmapbt(&mp->m_sb))
		return XFS_RMAP_BLOCK(mp) + 1;
	if (xfs_sb_version_hasfinobt(&mp->m_sb))
		return XFS_FIBT_BLOCK(mp) + 1;
	return XFS_IBT_BLOCK(mp) + 1;
}