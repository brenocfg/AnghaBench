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
typedef  scalar_t__ xfs_exntst_t ;
struct xfs_map_extent {int /*<<< orphan*/  me_flags; } ;
typedef  enum xfs_rmap_intent_type { ____Placeholder_xfs_rmap_intent_type } xfs_rmap_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int XFS_ATTR_FORK ; 
 scalar_t__ XFS_EXT_UNWRITTEN ; 
#define  XFS_RMAP_ALLOC 135 
#define  XFS_RMAP_CONVERT 134 
#define  XFS_RMAP_CONVERT_SHARED 133 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_ALLOC ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_CONVERT ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_CONVERT_SHARED ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_FREE ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_MAP ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_MAP_SHARED ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_UNMAP ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_UNMAP_SHARED ; 
 int /*<<< orphan*/  XFS_RMAP_EXTENT_UNWRITTEN ; 
#define  XFS_RMAP_FREE 132 
#define  XFS_RMAP_MAP 131 
#define  XFS_RMAP_MAP_SHARED 130 
#define  XFS_RMAP_UNMAP 129 
#define  XFS_RMAP_UNMAP_SHARED 128 

__attribute__((used)) static void
xfs_trans_set_rmap_flags(
	struct xfs_map_extent		*rmap,
	enum xfs_rmap_intent_type	type,
	int				whichfork,
	xfs_exntst_t			state)
{
	rmap->me_flags = 0;
	if (state == XFS_EXT_UNWRITTEN)
		rmap->me_flags |= XFS_RMAP_EXTENT_UNWRITTEN;
	if (whichfork == XFS_ATTR_FORK)
		rmap->me_flags |= XFS_RMAP_EXTENT_ATTR_FORK;
	switch (type) {
	case XFS_RMAP_MAP:
		rmap->me_flags |= XFS_RMAP_EXTENT_MAP;
		break;
	case XFS_RMAP_MAP_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_MAP_SHARED;
		break;
	case XFS_RMAP_UNMAP:
		rmap->me_flags |= XFS_RMAP_EXTENT_UNMAP;
		break;
	case XFS_RMAP_UNMAP_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_UNMAP_SHARED;
		break;
	case XFS_RMAP_CONVERT:
		rmap->me_flags |= XFS_RMAP_EXTENT_CONVERT;
		break;
	case XFS_RMAP_CONVERT_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_CONVERT_SHARED;
		break;
	case XFS_RMAP_ALLOC:
		rmap->me_flags |= XFS_RMAP_EXTENT_ALLOC;
		break;
	case XFS_RMAP_FREE:
		rmap->me_flags |= XFS_RMAP_EXTENT_FREE;
		break;
	default:
		ASSERT(0);
	}
}