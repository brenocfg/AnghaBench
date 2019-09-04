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
struct xfs_owner_info {int oi_flags; int /*<<< orphan*/  oi_offset; int /*<<< orphan*/  oi_owner; } ;

/* Variables and functions */
 int XFS_OWNER_INFO_ATTR_FORK ; 
 int XFS_OWNER_INFO_BMBT_BLOCK ; 
 unsigned int XFS_RMAP_ATTR_FORK ; 
 unsigned int XFS_RMAP_BMBT_BLOCK ; 

__attribute__((used)) static inline void
xfs_owner_info_unpack(
	struct xfs_owner_info	*oinfo,
	uint64_t		*owner,
	uint64_t		*offset,
	unsigned int		*flags)
{
	unsigned int		r = 0;

	*owner = oinfo->oi_owner;
	*offset = oinfo->oi_offset;
	if (oinfo->oi_flags & XFS_OWNER_INFO_ATTR_FORK)
		r |= XFS_RMAP_ATTR_FORK;
	if (oinfo->oi_flags & XFS_OWNER_INFO_BMBT_BLOCK)
		r |= XFS_RMAP_BMBT_BLOCK;
	*flags = r;
}