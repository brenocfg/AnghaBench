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
struct xfs_sb {int /*<<< orphan*/  sb_features2; int /*<<< orphan*/  sb_versionnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SB_VERSION2_ATTR2BIT ; 
 int /*<<< orphan*/  XFS_SB_VERSION_MOREBITSBIT ; 

__attribute__((used)) static inline void xfs_sb_version_addattr2(struct xfs_sb *sbp)
{
	sbp->sb_versionnum |= XFS_SB_VERSION_MOREBITSBIT;
	sbp->sb_features2 |= XFS_SB_VERSION2_ATTR2BIT;
}