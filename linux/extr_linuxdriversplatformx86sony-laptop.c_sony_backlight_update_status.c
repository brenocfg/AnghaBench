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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  sony_nc_acpi_handle ; 
 int sony_nc_int_call (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sony_backlight_update_status(struct backlight_device *bd)
{
	int arg = bd->props.brightness + 1;
	return sony_nc_int_call(sony_nc_acpi_handle, "SBRT", &arg, NULL);
}