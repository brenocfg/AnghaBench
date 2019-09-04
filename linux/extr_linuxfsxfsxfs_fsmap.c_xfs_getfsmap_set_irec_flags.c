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
struct xfs_rmap_irec {int /*<<< orphan*/  rm_flags; } ;
struct xfs_fsmap {int fmr_flags; } ;

/* Variables and functions */
 int FMR_OF_ATTR_FORK ; 
 int FMR_OF_EXTENT_MAP ; 
 int FMR_OF_PREALLOC ; 
 int /*<<< orphan*/  XFS_RMAP_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_RMAP_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_UNWRITTEN ; 

__attribute__((used)) static void
xfs_getfsmap_set_irec_flags(
	struct xfs_rmap_irec	*irec,
	struct xfs_fsmap	*fmr)
{
	irec->rm_flags = 0;
	if (fmr->fmr_flags & FMR_OF_ATTR_FORK)
		irec->rm_flags |= XFS_RMAP_ATTR_FORK;
	if (fmr->fmr_flags & FMR_OF_EXTENT_MAP)
		irec->rm_flags |= XFS_RMAP_BMBT_BLOCK;
	if (fmr->fmr_flags & FMR_OF_PREALLOC)
		irec->rm_flags |= XFS_RMAP_UNWRITTEN;
}