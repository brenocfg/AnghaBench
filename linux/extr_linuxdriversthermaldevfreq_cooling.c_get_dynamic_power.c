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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct devfreq_cooling_power {unsigned long (* get_dynamic_power ) (int /*<<< orphan*/ ,unsigned long,unsigned long) ;scalar_t__ dyn_power_coeff; } ;
struct devfreq_cooling_device {int /*<<< orphan*/  devfreq; struct devfreq_cooling_power* power_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 unsigned long stub1 (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long
get_dynamic_power(struct devfreq_cooling_device *dfc, unsigned long freq,
		  unsigned long voltage)
{
	u64 power;
	u32 freq_mhz;
	struct devfreq_cooling_power *dfc_power = dfc->power_ops;

	if (dfc_power->get_dynamic_power)
		return dfc_power->get_dynamic_power(dfc->devfreq, freq,
						    voltage);

	freq_mhz = freq / 1000000;
	power = (u64)dfc_power->dyn_power_coeff * freq_mhz * voltage * voltage;
	do_div(power, 1000000000);

	return power;
}