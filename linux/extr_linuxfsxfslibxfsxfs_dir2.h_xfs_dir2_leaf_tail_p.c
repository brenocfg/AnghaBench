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
struct xfs_dir2_leaf_tail {int dummy; } ;
struct xfs_dir2_leaf {int dummy; } ;
struct xfs_da_geometry {int blksize; } ;

/* Variables and functions */

__attribute__((used)) static inline struct xfs_dir2_leaf_tail *
xfs_dir2_leaf_tail_p(struct xfs_da_geometry *geo, struct xfs_dir2_leaf *lp)
{
	return (struct xfs_dir2_leaf_tail *)
		((char *)lp + geo->blksize -
		  sizeof(struct xfs_dir2_leaf_tail));
}