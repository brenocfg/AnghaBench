#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int kbd_type; scalar_t__ kbd_mode; TYPE_2__* acpi_dev; int /*<<< orphan*/  kbd_led; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_class; } ;
struct TYPE_6__ {TYPE_4__ dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ SCI_KBD_MODE_AUTO ; 
 scalar_t__ SCI_KBD_MODE_ON ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  led_classdev_notify_brightness_hw_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sysfs_update_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* toshiba_acpi ; 
 int /*<<< orphan*/  toshiba_attr_group ; 

__attribute__((used)) static void toshiba_acpi_kbd_bl_work(struct work_struct *work)
{
	/* Update the sysfs entries */
	if (sysfs_update_group(&toshiba_acpi->acpi_dev->dev.kobj,
			       &toshiba_attr_group))
		pr_err("Unable to update sysfs entries\n");

	/* Notify LED subsystem about keyboard backlight change */
	if (toshiba_acpi->kbd_type == 2 &&
	    toshiba_acpi->kbd_mode != SCI_KBD_MODE_AUTO)
		led_classdev_notify_brightness_hw_changed(&toshiba_acpi->kbd_led,
				(toshiba_acpi->kbd_mode == SCI_KBD_MODE_ON) ?
				LED_FULL : LED_OFF);

	/* Emulate the keyboard backlight event */
	acpi_bus_generate_netlink_event(toshiba_acpi->acpi_dev->pnp.device_class,
					dev_name(&toshiba_acpi->acpi_dev->dev),
					0x92, 0);
}