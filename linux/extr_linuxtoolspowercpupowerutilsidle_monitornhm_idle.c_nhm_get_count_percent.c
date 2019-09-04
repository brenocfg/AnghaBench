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
 double** current_count ; 
 int /*<<< orphan*/  dprint (char*,int /*<<< orphan*/ ,double,double,double,...) ; 
 int /*<<< orphan*/ * is_valid ; 
 TYPE_1__* nhm_cstates ; 
 double** previous_count ; 
 double tsc_at_measure_end ; 
 double tsc_at_measure_start ; 

__attribute__((used)) static int nhm_get_count_percent(unsigned int id, double *percent,
				 unsigned int cpu)
{
	*percent = 0.0;

	if (!is_valid[cpu])
		return -1;

	*percent = (100.0 *
		(current_count[id][cpu] - previous_count[id][cpu])) /
		(tsc_at_measure_end - tsc_at_measure_start);

	dprint("%s: previous: %llu - current: %llu - (%u)\n",
		nhm_cstates[id].name, previous_count[id][cpu],
		current_count[id][cpu], cpu);

	dprint("%s: tsc_diff: %llu - count_diff: %llu - percent: %2.f (%u)\n",
	       nhm_cstates[id].name,
	       (unsigned long long) tsc_at_measure_end - tsc_at_measure_start,
	       current_count[id][cpu] - previous_count[id][cpu],
	       *percent, cpu);

	return 0;
}