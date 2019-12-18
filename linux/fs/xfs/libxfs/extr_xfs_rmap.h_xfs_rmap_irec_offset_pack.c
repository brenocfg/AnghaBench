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
struct xfs_rmap_irec {int rm_flags; int /*<<< orphan*/  rm_offset; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int XFS_RMAP_ATTR_FORK ; 
 int XFS_RMAP_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_RMAP_OFF_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_RMAP_OFF_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_OFF_UNWRITTEN ; 
 int XFS_RMAP_UNWRITTEN ; 

__attribute__((used)) static inline __u64
xfs_rmap_irec_offset_pack(
	const struct xfs_rmap_irec	*irec)
{
	__u64			x;

	x = XFS_RMAP_OFF(irec->rm_offset);
	if (irec->rm_flags & XFS_RMAP_ATTR_FORK)
		x |= XFS_RMAP_OFF_ATTR_FORK;
	if (irec->rm_flags & XFS_RMAP_BMBT_BLOCK)
		x |= XFS_RMAP_OFF_BMBT_BLOCK;
	if (irec->rm_flags & XFS_RMAP_UNWRITTEN)
		x |= XFS_RMAP_OFF_UNWRITTEN;
	return x;
}