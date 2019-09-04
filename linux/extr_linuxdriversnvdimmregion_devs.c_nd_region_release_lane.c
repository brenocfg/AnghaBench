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
struct nd_region {scalar_t__ num_lanes; int /*<<< orphan*/  lane; } ;
struct nd_percpu_lane {scalar_t__ count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int get_cpu () ; 
 scalar_t__ nr_cpu_ids ; 
 struct nd_percpu_lane* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nd_region_release_lane(struct nd_region *nd_region, unsigned int lane)
{
	if (nd_region->num_lanes < nr_cpu_ids) {
		unsigned int cpu = get_cpu();
		struct nd_percpu_lane *ndl_lock, *ndl_count;

		ndl_count = per_cpu_ptr(nd_region->lane, cpu);
		ndl_lock = per_cpu_ptr(nd_region->lane, lane);
		if (--ndl_count->count == 0)
			spin_unlock(&ndl_lock->lock);
		put_cpu();
	}
	put_cpu();
}