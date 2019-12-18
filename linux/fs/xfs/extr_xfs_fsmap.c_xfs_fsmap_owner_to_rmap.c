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
struct xfs_fsmap {int fmr_flags; int fmr_owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMR_OF_SPECIAL_OWNER ; 
#define  XFS_FMR_OWN_AG 137 
#define  XFS_FMR_OWN_COW 136 
#define  XFS_FMR_OWN_DEFECTIVE 135 
#define  XFS_FMR_OWN_FREE 134 
#define  XFS_FMR_OWN_FS 133 
#define  XFS_FMR_OWN_INOBT 132 
#define  XFS_FMR_OWN_INODES 131 
#define  XFS_FMR_OWN_LOG 130 
#define  XFS_FMR_OWN_REFC 129 
#define  XFS_FMR_OWN_UNKNOWN 128 
 int XFS_RMAP_OWN_AG ; 
 int XFS_RMAP_OWN_COW ; 
 int XFS_RMAP_OWN_FS ; 
 int XFS_RMAP_OWN_INOBT ; 
 int XFS_RMAP_OWN_INODES ; 
 int XFS_RMAP_OWN_LOG ; 
 int XFS_RMAP_OWN_NULL ; 
 int XFS_RMAP_OWN_REFC ; 
 int XFS_RMAP_OWN_UNKNOWN ; 

__attribute__((used)) static int
xfs_fsmap_owner_to_rmap(
	struct xfs_rmap_irec	*dest,
	struct xfs_fsmap	*src)
{
	if (!(src->fmr_flags & FMR_OF_SPECIAL_OWNER)) {
		dest->rm_owner = src->fmr_owner;
		return 0;
	}

	switch (src->fmr_owner) {
	case 0:			/* "lowest owner id possible" */
	case -1ULL:		/* "highest owner id possible" */
		dest->rm_owner = 0;
		break;
	case XFS_FMR_OWN_FREE:
		dest->rm_owner = XFS_RMAP_OWN_NULL;
		break;
	case XFS_FMR_OWN_UNKNOWN:
		dest->rm_owner = XFS_RMAP_OWN_UNKNOWN;
		break;
	case XFS_FMR_OWN_FS:
		dest->rm_owner = XFS_RMAP_OWN_FS;
		break;
	case XFS_FMR_OWN_LOG:
		dest->rm_owner = XFS_RMAP_OWN_LOG;
		break;
	case XFS_FMR_OWN_AG:
		dest->rm_owner = XFS_RMAP_OWN_AG;
		break;
	case XFS_FMR_OWN_INOBT:
		dest->rm_owner = XFS_RMAP_OWN_INOBT;
		break;
	case XFS_FMR_OWN_INODES:
		dest->rm_owner = XFS_RMAP_OWN_INODES;
		break;
	case XFS_FMR_OWN_REFC:
		dest->rm_owner = XFS_RMAP_OWN_REFC;
		break;
	case XFS_FMR_OWN_COW:
		dest->rm_owner = XFS_RMAP_OWN_COW;
		break;
	case XFS_FMR_OWN_DEFECTIVE:	/* not implemented */
		/* fall through */
	default:
		return -EINVAL;
	}
	return 0;
}