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
struct ceph_osds {scalar_t__ primary; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ calc_pg_rank (scalar_t__,struct ceph_osds const*) ; 

__attribute__((used)) static bool primary_changed(const struct ceph_osds *old_acting,
			    const struct ceph_osds *new_acting)
{
	if (!old_acting->size && !new_acting->size)
		return false; /* both still empty */

	if (!old_acting->size ^ !new_acting->size)
		return true; /* was empty, now not, or vice versa */

	if (old_acting->primary != new_acting->primary)
		return true; /* primary changed */

	if (calc_pg_rank(old_acting->primary, old_acting) !=
	    calc_pg_rank(new_acting->primary, new_acting))
		return true;

	return false; /* same primary (tho replicas may have changed) */
}