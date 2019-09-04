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
struct xfs_rmap_irec {int rm_owner; } ;
struct xfs_fsmap {int fmr_owner; int /*<<< orphan*/  fmr_flags; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  FMR_OF_SPECIAL_OWNER ; 
 int XFS_FMR_OWN_AG ; 
 int XFS_FMR_OWN_COW ; 
 int XFS_FMR_OWN_FREE ; 
 int XFS_FMR_OWN_FS ; 
 int XFS_FMR_OWN_INOBT ; 
 int XFS_FMR_OWN_INODES ; 
 int XFS_FMR_OWN_LOG ; 
 int XFS_FMR_OWN_REFC ; 
 int /*<<< orphan*/  XFS_RMAP_NON_INODE_OWNER (int) ; 
#define  XFS_RMAP_OWN_AG 135 
#define  XFS_RMAP_OWN_COW 134 
#define  XFS_RMAP_OWN_FS 133 
#define  XFS_RMAP_OWN_INOBT 132 
#define  XFS_RMAP_OWN_INODES 131 
#define  XFS_RMAP_OWN_LOG 130 
#define  XFS_RMAP_OWN_NULL 129 
#define  XFS_RMAP_OWN_REFC 128 

__attribute__((used)) static int
xfs_fsmap_owner_from_rmap(
	struct xfs_fsmap	*dest,
	struct xfs_rmap_irec	*src)
{
	dest->fmr_flags = 0;
	if (!XFS_RMAP_NON_INODE_OWNER(src->rm_owner)) {
		dest->fmr_owner = src->rm_owner;
		return 0;
	}
	dest->fmr_flags |= FMR_OF_SPECIAL_OWNER;

	switch (src->rm_owner) {
	case XFS_RMAP_OWN_FS:
		dest->fmr_owner = XFS_FMR_OWN_FS;
		break;
	case XFS_RMAP_OWN_LOG:
		dest->fmr_owner = XFS_FMR_OWN_LOG;
		break;
	case XFS_RMAP_OWN_AG:
		dest->fmr_owner = XFS_FMR_OWN_AG;
		break;
	case XFS_RMAP_OWN_INOBT:
		dest->fmr_owner = XFS_FMR_OWN_INOBT;
		break;
	case XFS_RMAP_OWN_INODES:
		dest->fmr_owner = XFS_FMR_OWN_INODES;
		break;
	case XFS_RMAP_OWN_REFC:
		dest->fmr_owner = XFS_FMR_OWN_REFC;
		break;
	case XFS_RMAP_OWN_COW:
		dest->fmr_owner = XFS_FMR_OWN_COW;
		break;
	case XFS_RMAP_OWN_NULL:	/* "free" */
		dest->fmr_owner = XFS_FMR_OWN_FREE;
		break;
	default:
		return -EFSCORRUPTED;
	}
	return 0;
}