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
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
typedef  int xfs_dablk_t ;
struct xfs_da_geometry {int blklog; int fsblog; } ;

/* Variables and functions */

__attribute__((used)) static inline xfs_dir2_db_t
xfs_dir2_da_to_db(struct xfs_da_geometry *geo, xfs_dablk_t da)
{
	return (xfs_dir2_db_t)(da >> (geo->blklog - geo->fsblog));
}