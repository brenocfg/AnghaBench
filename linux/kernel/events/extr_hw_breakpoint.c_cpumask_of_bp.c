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
struct perf_event {scalar_t__ cpu; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask const* cpu_possible_mask ; 
 struct cpumask const* cpumask_of (scalar_t__) ; 

__attribute__((used)) static const struct cpumask *cpumask_of_bp(struct perf_event *bp)
{
	if (bp->cpu >= 0)
		return cpumask_of(bp->cpu);
	return cpu_possible_mask;
}