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
typedef  int uint ;
struct xfs_dir3_leaf_hdr {int dummy; } ;
struct xfs_dir2_leaf_entry {int dummy; } ;
struct xfs_da_geometry {int blksize; } ;

/* Variables and functions */

__attribute__((used)) static int
xfs_dir3_max_leaf_ents(struct xfs_da_geometry *geo)
{
	return (geo->blksize - sizeof(struct xfs_dir3_leaf_hdr)) /
		(uint)sizeof(struct xfs_dir2_leaf_entry);
}