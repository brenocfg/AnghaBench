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
typedef  int /*<<< orphan*/  u64 ;
struct sugov_policy {struct cpufreq_policy* policy; } ;
struct cpufreq_policy {unsigned int cur; } ;

/* Variables and functions */
 unsigned int cpufreq_driver_fast_switch (struct cpufreq_policy*,unsigned int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  sugov_update_next_freq (struct sugov_policy*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_cpu_frequency (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sugov_fast_switch(struct sugov_policy *sg_policy, u64 time,
			      unsigned int next_freq)
{
	struct cpufreq_policy *policy = sg_policy->policy;

	if (!sugov_update_next_freq(sg_policy, time, next_freq))
		return;

	next_freq = cpufreq_driver_fast_switch(policy, next_freq);
	if (!next_freq)
		return;

	policy->cur = next_freq;
	trace_cpu_frequency(next_freq, smp_processor_id());
}