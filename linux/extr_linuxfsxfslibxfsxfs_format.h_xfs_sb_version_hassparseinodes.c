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
struct xfs_sb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SB_FEAT_INCOMPAT_SPINODES ; 
 scalar_t__ XFS_SB_VERSION_5 ; 
 scalar_t__ XFS_SB_VERSION_NUM (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_has_incompat_feature (struct xfs_sb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xfs_sb_version_hassparseinodes(struct xfs_sb *sbp)
{
	return XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		xfs_sb_has_incompat_feature(sbp, XFS_SB_FEAT_INCOMPAT_SPINODES);
}