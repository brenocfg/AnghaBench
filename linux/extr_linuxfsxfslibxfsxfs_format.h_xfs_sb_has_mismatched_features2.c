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
struct xfs_sb {scalar_t__ sb_bad_features2; scalar_t__ sb_features2; } ;

/* Variables and functions */

__attribute__((used)) static inline bool xfs_sb_has_mismatched_features2(struct xfs_sb *sbp)
{
	return sbp->sb_bad_features2 != sbp->sb_features2;
}