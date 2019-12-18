#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct fib6_info {TYPE_1__* fib6_nh; } ;
struct TYPE_2__ {int /*<<< orphan*/  fib_nh_upper_bound; scalar_t__ fib_nh_weight; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt6_is_dead (struct fib6_info*) ; 

__attribute__((used)) static void rt6_upper_bound_set(struct fib6_info *rt, int *weight, int total)
{
	int upper_bound = -1;

	if (!rt6_is_dead(rt)) {
		*weight += rt->fib6_nh->fib_nh_weight;
		upper_bound = DIV_ROUND_CLOSEST_ULL((u64) (*weight) << 31,
						    total) - 1;
	}
	atomic_set(&rt->fib6_nh->fib_nh_upper_bound, upper_bound);
}