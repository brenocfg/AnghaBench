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
struct cpufreq_frequencies {struct cpufreq_frequencies* next; struct cpufreq_frequencies* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cpufreq_frequencies*) ; 

void cpufreq_put_frequencies(struct cpufreq_frequencies *any)
{
	struct cpufreq_frequencies *tmp, *next;

	if (!any)
		return;

	tmp = any->first;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}