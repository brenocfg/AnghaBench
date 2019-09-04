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
struct musb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void davinci_musb_source_power(struct musb *musb, int is_on, int immediate)
{
#ifdef CONFIG_MACH_DAVINCI_EVM
	if (is_on)
		is_on = 1;

	if (vbus_state == is_on)
		return;
	vbus_state = !is_on;		/* 0/1 vs "-1 == unknown/init" */

	if (machine_is_davinci_evm()) {
		static DECLARE_WORK(evm_vbus_work, evm_deferred_drvvbus);

		if (immediate)
			gpio_set_value_cansleep(GPIO_nVBUS_DRV, vbus_state);
		else
			schedule_work(&evm_vbus_work);
	}
	if (immediate)
		vbus_state = is_on;
#endif
}