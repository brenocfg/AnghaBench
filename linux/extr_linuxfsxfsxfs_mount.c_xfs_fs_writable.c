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
struct xfs_mount {int m_flags; TYPE_2__* m_super; } ;
struct TYPE_3__ {int frozen; } ;
struct TYPE_4__ {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SB_UNFROZEN ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int XFS_MOUNT_RDONLY ; 

bool
xfs_fs_writable(
	struct xfs_mount	*mp,
	int			level)
{
	ASSERT(level > SB_UNFROZEN);
	if ((mp->m_super->s_writers.frozen >= level) ||
	    XFS_FORCED_SHUTDOWN(mp) || (mp->m_flags & XFS_MOUNT_RDONLY))
		return false;

	return true;
}