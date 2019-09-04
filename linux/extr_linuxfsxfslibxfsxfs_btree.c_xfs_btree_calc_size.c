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

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

unsigned long long
xfs_btree_calc_size(
	uint			*limits,
	unsigned long long	len)
{
	int			level;
	int			maxrecs;
	unsigned long long	rval;

	maxrecs = limits[0];
	for (level = 0, rval = 0; len > 1; level++) {
		len += maxrecs - 1;
		do_div(len, maxrecs);
		maxrecs = limits[1];
		rval += len;
	}
	return rval;
}