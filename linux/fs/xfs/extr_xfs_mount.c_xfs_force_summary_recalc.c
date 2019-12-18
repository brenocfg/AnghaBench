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
 int /*<<< orphan*/  XFS_SICK_FS_COUNTERS ; 
 int /*<<< orphan*/  xfs_fs_mark_sick (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_haslazysbcount (int /*<<< orphan*/ *) ; 

void
xfs_force_summary_recalc(
	struct xfs_mount	*mp)
{
	if (!xfs_sb_version_haslazysbcount(&mp->m_sb))
		return;

	xfs_fs_mark_sick(mp, XFS_SICK_FS_COUNTERS);
}