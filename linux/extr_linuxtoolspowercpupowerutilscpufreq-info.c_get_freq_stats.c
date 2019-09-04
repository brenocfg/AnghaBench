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
struct cpufreq_stats {double time_in_state; struct cpufreq_stats* next; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 struct cpufreq_stats* cpufreq_get_stats (unsigned int,unsigned long long*) ; 
 unsigned long cpufreq_get_transitions (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_stats (struct cpufreq_stats*) ; 
 int /*<<< orphan*/  print_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_freq_stats(unsigned int cpu, unsigned int human)
{
	unsigned long total_trans = cpufreq_get_transitions(cpu);
	unsigned long long total_time;
	struct cpufreq_stats *stats = cpufreq_get_stats(cpu, &total_time);
	while (stats) {
		if (human) {
			print_speed(stats->frequency);
			printf(":%.2f%%",
				(100.0 * stats->time_in_state) / total_time);
		} else
			printf("%lu:%llu",
				stats->frequency, stats->time_in_state);
		stats = stats->next;
		if (stats)
			printf(", ");
	}
	cpufreq_put_stats(stats);
	if (total_trans)
		printf("  (%lu)\n", total_trans);
	return 0;
}