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
struct TYPE_2__ {int /*<<< orphan*/  hwp_max; int /*<<< orphan*/  hwp_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_hwp ; 
 int /*<<< orphan*/  hwp_update_enabled () ; 
 TYPE_1__ req_update ; 
 int /*<<< orphan*/  update_cpufreq_scaling_freq (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ update_hwp_max ; 
 scalar_t__ update_hwp_min ; 

int update_sysfs(int cpu)
{
	if (!has_hwp)
		return 0;

	if (!hwp_update_enabled())
		return 0;

	if (access("/sys/devices/system/cpu/cpu0/cpufreq", F_OK))
		return 0;

	if (update_hwp_min)
		update_cpufreq_scaling_freq(0, cpu, req_update.hwp_min);

	if (update_hwp_max)
		update_cpufreq_scaling_freq(1, cpu, req_update.hwp_max);

	return 0;
}