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
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_owner_info {int /*<<< orphan*/  oi_flags; int /*<<< orphan*/  oi_offset; int /*<<< orphan*/  oi_owner; } ;

/* Variables and functions */
 int XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_OWNER_INFO_ATTR_FORK ; 

__attribute__((used)) static inline void
xfs_rmap_ino_owner(
	struct xfs_owner_info	*oi,
	xfs_ino_t		ino,
	int			whichfork,
	xfs_fileoff_t		offset)
{
	oi->oi_owner = ino;
	oi->oi_offset = offset;
	oi->oi_flags = 0;
	if (whichfork == XFS_ATTR_FORK)
		oi->oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
}