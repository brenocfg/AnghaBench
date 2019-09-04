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
typedef  int /*<<< orphan*/  u64 ;
struct nd_region {struct nd_interleave_set* nd_set; } ;
struct nd_interleave_set {int /*<<< orphan*/  altcookie; } ;

/* Variables and functions */

u64 nd_region_interleave_set_altcookie(struct nd_region *nd_region)
{
	struct nd_interleave_set *nd_set = nd_region->nd_set;

	if (nd_set)
		return nd_set->altcookie;
	return 0;
}