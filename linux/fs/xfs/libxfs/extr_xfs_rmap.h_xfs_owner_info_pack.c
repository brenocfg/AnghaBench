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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_owner_info {int /*<<< orphan*/  oi_flags; int /*<<< orphan*/  oi_offset; int /*<<< orphan*/  oi_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_OWNER_INFO_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_OWNER_INFO_BMBT_BLOCK ; 
 unsigned int XFS_RMAP_ATTR_FORK ; 
 unsigned int XFS_RMAP_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_OFF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xfs_owner_info_pack(
	struct xfs_owner_info	*oinfo,
	uint64_t		owner,
	uint64_t		offset,
	unsigned int		flags)
{
	oinfo->oi_owner = owner;
	oinfo->oi_offset = XFS_RMAP_OFF(offset);
	oinfo->oi_flags = 0;
	if (flags & XFS_RMAP_ATTR_FORK)
		oinfo->oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
	if (flags & XFS_RMAP_BMBT_BLOCK)
		oinfo->oi_flags |= XFS_OWNER_INFO_BMBT_BLOCK;
}