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
typedef  int uint32_t ;
struct xfs_sb {int sb_features_ro_compat; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
xfs_sb_has_ro_compat_feature(
	struct xfs_sb	*sbp,
	uint32_t	feature)
{
	return (sbp->sb_features_ro_compat & feature) != 0;
}