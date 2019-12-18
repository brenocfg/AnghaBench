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
struct cpufreq_available_governors {struct cpufreq_available_governors* governor; struct cpufreq_available_governors* next; struct cpufreq_available_governors* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cpufreq_available_governors*) ; 

void cpufreq_put_available_governors(struct cpufreq_available_governors *any)
{
	struct cpufreq_available_governors *tmp, *next;

	if (!any)
		return;

	tmp = any->first;
	while (tmp) {
		next = tmp->next;
		if (tmp->governor)
			free(tmp->governor);
		free(tmp);
		tmp = next;
	}
}