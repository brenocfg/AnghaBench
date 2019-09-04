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
 int /*<<< orphan*/  dell_smbios_wmi_driver ; 
 int /*<<< orphan*/  wmi_driver_unregister (int /*<<< orphan*/ *) ; 

void exit_dell_smbios_wmi(void)
{
	wmi_driver_unregister(&dell_smbios_wmi_driver);
}