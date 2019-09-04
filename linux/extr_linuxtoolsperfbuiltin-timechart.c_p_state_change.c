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
typedef  int u64 ;
struct timechart {int first_time; int max_freq; int min_freq; int turbo_frequency; struct power_event* power_events; } ;
struct power_event {int state; int start_time; int end_time; int cpu; struct power_event* next; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSTATE ; 
 int* cpus_pstate_start_times ; 
 int* cpus_pstate_state ; 
 struct power_event* zalloc (int) ; 

__attribute__((used)) static void p_state_change(struct timechart *tchart, int cpu, u64 timestamp, u64 new_freq)
{
	struct power_event *pwr;

	if (new_freq > 8000000) /* detect invalid data */
		return;

	pwr = zalloc(sizeof(*pwr));
	if (!pwr)
		return;

	pwr->state = cpus_pstate_state[cpu];
	pwr->start_time = cpus_pstate_start_times[cpu];
	pwr->end_time = timestamp;
	pwr->cpu = cpu;
	pwr->type = PSTATE;
	pwr->next = tchart->power_events;

	if (!pwr->start_time)
		pwr->start_time = tchart->first_time;

	tchart->power_events = pwr;

	cpus_pstate_state[cpu] = new_freq;
	cpus_pstate_start_times[cpu] = timestamp;

	if ((u64)new_freq > tchart->max_freq)
		tchart->max_freq = new_freq;

	if (new_freq < tchart->min_freq || tchart->min_freq == 0)
		tchart->min_freq = new_freq;

	if (new_freq == tchart->max_freq - 1000)
		tchart->turbo_frequency = tchart->max_freq;
}