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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dell_smbios_wmi_driver ; 
 int /*<<< orphan*/  dmi_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_b1 ; 
 int wmi_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmi_supported ; 

int init_dell_smbios_wmi(void)
{
	dmi_walk(find_b1, NULL);

	if (!wmi_supported)
		return -ENODEV;

	return wmi_driver_register(&dell_smbios_wmi_driver);
}