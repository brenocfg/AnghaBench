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
struct sugov_policy {unsigned int cached_raw_freq; int need_freq_update; unsigned int next_freq; struct cpufreq_policy* policy; } ;
struct TYPE_2__ {unsigned int max_freq; } ;
struct cpufreq_policy {unsigned int cur; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 scalar_t__ arch_scale_freq_invariant () ; 
 unsigned int cpufreq_driver_resolve_freq (struct cpufreq_policy*,unsigned int) ; 
 unsigned int map_util_freq (unsigned long,unsigned int,unsigned long) ; 

__attribute__((used)) static unsigned int get_next_freq(struct sugov_policy *sg_policy,
				  unsigned long util, unsigned long max)
{
	struct cpufreq_policy *policy = sg_policy->policy;
	unsigned int freq = arch_scale_freq_invariant() ?
				policy->cpuinfo.max_freq : policy->cur;

	freq = map_util_freq(util, freq, max);

	if (freq == sg_policy->cached_raw_freq && !sg_policy->need_freq_update)
		return sg_policy->next_freq;

	sg_policy->need_freq_update = false;
	sg_policy->cached_raw_freq = freq;
	return cpufreq_driver_resolve_freq(policy, freq);
}