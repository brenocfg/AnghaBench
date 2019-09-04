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
 scalar_t__ acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int /*<<< orphan*/  pr_notice (char*) ; 

__attribute__((used)) static void tpacpi_disable_brightness_delay(void)
{
	if (acpi_evalf(hkey_handle, NULL, "PWMS", "qvd", 0))
		pr_notice("ACPI backlight control delay disabled\n");
}