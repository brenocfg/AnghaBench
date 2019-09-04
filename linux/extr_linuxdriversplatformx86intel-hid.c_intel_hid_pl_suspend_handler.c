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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_button_array_enable (struct device*,int) ; 
 int /*<<< orphan*/  intel_hid_set_enable (struct device*,int) ; 
 scalar_t__ pm_suspend_via_firmware () ; 

__attribute__((used)) static int intel_hid_pl_suspend_handler(struct device *device)
{
	if (pm_suspend_via_firmware()) {
		intel_hid_set_enable(device, false);
		intel_button_array_enable(device, false);
	}
	return 0;
}