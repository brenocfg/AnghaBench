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
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct xfs_dir3_free_hdr {int dummy; } ;
struct xfs_da_geometry {int blksize; } ;

/* Variables and functions */

__attribute__((used)) static int
xfs_dir3_free_max_bests(struct xfs_da_geometry *geo)
{
	return (geo->blksize - sizeof(struct xfs_dir3_free_hdr)) /
		sizeof(xfs_dir2_data_off_t);
}