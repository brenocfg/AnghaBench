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
struct xfs_sb {int sb_versionnum; int sb_features2; } ;

/* Variables and functions */
 int XFS_SB_VERSION2_OKBITS ; 
 int XFS_SB_VERSION_DIRV2BIT ; 
 int XFS_SB_VERSION_MOREBITSBIT ; 
 int XFS_SB_VERSION_OKBITS ; 

__attribute__((used)) static inline bool xfs_sb_good_v4_features(struct xfs_sb *sbp)
{
	if (!(sbp->sb_versionnum & XFS_SB_VERSION_DIRV2BIT))
		return false;

	/* check for unknown features in the fs */
	if ((sbp->sb_versionnum & ~XFS_SB_VERSION_OKBITS) ||
	    ((sbp->sb_versionnum & XFS_SB_VERSION_MOREBITSBIT) &&
	     (sbp->sb_features2 & ~XFS_SB_VERSION2_OKBITS)))
		return false;

	return true;
}