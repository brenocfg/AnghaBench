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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* cpuidle_cstates ; 
 unsigned long long** current_count ; 
 int /*<<< orphan*/  dprint (char*,int /*<<< orphan*/ ,double,unsigned long long,double,...) ; 
 unsigned long long** previous_count ; 
 double timediff ; 

__attribute__((used)) static int cpuidle_get_count_percent(unsigned int id, double *percent,
				     unsigned int cpu)
{
	unsigned long long statediff = current_count[cpu][id]
		- previous_count[cpu][id];
	dprint("%s: - diff: %llu - percent: %f (%u)\n",
	       cpuidle_cstates[id].name, timediff, *percent, cpu);

	if (timediff == 0)
		*percent = 0.0;
	else
		*percent = ((100.0 * statediff) / timediff);

	dprint("%s: - timediff: %llu - statediff: %llu - percent: %f (%u)\n",
	       cpuidle_cstates[id].name, timediff, statediff, *percent, cpu);

	return 0;
}