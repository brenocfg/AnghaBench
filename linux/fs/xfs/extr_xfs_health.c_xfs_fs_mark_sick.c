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
struct xfs_mount {unsigned int m_fs_sick; unsigned int m_fs_checked; int /*<<< orphan*/  m_sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int XFS_SICK_FS_PRIMARY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_fs_mark_sick (struct xfs_mount*,unsigned int) ; 

void
xfs_fs_mark_sick(
	struct xfs_mount	*mp,
	unsigned int		mask)
{
	ASSERT(!(mask & ~XFS_SICK_FS_PRIMARY));
	trace_xfs_fs_mark_sick(mp, mask);

	spin_lock(&mp->m_sb_lock);
	mp->m_fs_sick |= mask;
	mp->m_fs_checked |= mask;
	spin_unlock(&mp->m_sb_lock);
}