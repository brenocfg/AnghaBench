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
 int XFS_COW_FORK ; 
 scalar_t__ xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
xfs_rmap_update_is_needed(
	struct xfs_mount	*mp,
	int			whichfork)
{
	return xfs_sb_version_hasrmapbt(&mp->m_sb) && whichfork != XFS_COW_FORK;
}