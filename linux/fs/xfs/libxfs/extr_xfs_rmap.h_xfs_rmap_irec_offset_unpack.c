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
struct xfs_rmap_irec {int /*<<< orphan*/  rm_flags; int /*<<< orphan*/  rm_offset; } ;
typedef  int __u64 ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_RMAP_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_RMAP_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_OFF (int) ; 
 int XFS_RMAP_OFF_ATTR_FORK ; 
 int XFS_RMAP_OFF_BMBT_BLOCK ; 
 int XFS_RMAP_OFF_FLAGS ; 
 int XFS_RMAP_OFF_MASK ; 
 int XFS_RMAP_OFF_UNWRITTEN ; 
 int /*<<< orphan*/  XFS_RMAP_UNWRITTEN ; 

__attribute__((used)) static inline int
xfs_rmap_irec_offset_unpack(
	__u64			offset,
	struct xfs_rmap_irec	*irec)
{
	if (offset & ~(XFS_RMAP_OFF_MASK | XFS_RMAP_OFF_FLAGS))
		return -EFSCORRUPTED;
	irec->rm_offset = XFS_RMAP_OFF(offset);
	irec->rm_flags = 0;
	if (offset & XFS_RMAP_OFF_ATTR_FORK)
		irec->rm_flags |= XFS_RMAP_ATTR_FORK;
	if (offset & XFS_RMAP_OFF_BMBT_BLOCK)
		irec->rm_flags |= XFS_RMAP_BMBT_BLOCK;
	if (offset & XFS_RMAP_OFF_UNWRITTEN)
		irec->rm_flags |= XFS_RMAP_UNWRITTEN;
	return 0;
}