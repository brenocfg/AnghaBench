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
typedef  unsigned long uint ;

/* Variables and functions */

uint
xfs_btree_compute_maxlevels(
	uint			*limits,
	unsigned long		len)
{
	uint			level;
	unsigned long		maxblocks;

	maxblocks = (len + limits[0] - 1) / limits[0];
	for (level = 1; maxblocks > 1; level++)
		maxblocks = (maxblocks + limits[1] - 1) / limits[1];
	return level;
}