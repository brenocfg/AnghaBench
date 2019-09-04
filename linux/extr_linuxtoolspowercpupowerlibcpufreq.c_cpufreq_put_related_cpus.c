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
struct cpufreq_affected_cpus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_put_affected_cpus (struct cpufreq_affected_cpus*) ; 

void cpufreq_put_related_cpus(struct cpufreq_affected_cpus *any)
{
	cpufreq_put_affected_cpus(any);
}