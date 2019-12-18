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
struct ceph_osds {scalar_t__ size; int primary; scalar_t__* osds; } ;

/* Variables and functions */
 scalar_t__ CRUSH_ITEM_NONE ; 

__attribute__((used)) static bool osds_valid(const struct ceph_osds *set)
{
	/* non-empty set */
	if (set->size > 0 && set->primary >= 0)
		return true;

	/* empty can_shift_osds set */
	if (!set->size && set->primary == -1)
		return true;

	/* empty !can_shift_osds set - all NONE */
	if (set->size > 0 && set->primary == -1) {
		int i;

		for (i = 0; i < set->size; i++) {
			if (set->osds[i] != CRUSH_ITEM_NONE)
				break;
		}
		if (i == set->size)
			return true;
	}

	return false;
}