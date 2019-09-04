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
struct xfs_sb {int sb_versionnum; } ;

/* Variables and functions */
 int XFS_SB_VERSION_SECTORBIT ; 

__attribute__((used)) static inline bool xfs_sb_version_hassector(struct xfs_sb *sbp)
{
	return (sbp->sb_versionnum & XFS_SB_VERSION_SECTORBIT);
}