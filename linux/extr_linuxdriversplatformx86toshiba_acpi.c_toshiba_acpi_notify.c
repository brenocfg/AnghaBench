#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct toshiba_acpi_dev {int kbd_event_generated; int kbd_type; int /*<<< orphan*/  last_key_event; int /*<<< orphan*/  kbd_mode; int /*<<< orphan*/  kbd_led; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {TYPE_2__ dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  SCI_KBD_MODE_AUTO ; 
 int /*<<< orphan*/  SCI_KBD_MODE_ON ; 
 int /*<<< orphan*/  TOSHIBA_WMI_EVENT_GUID ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct toshiba_acpi_dev* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  led_classdev_notify_brightness_hw_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  sysfs_update_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toshiba_acpi_process_hotkeys (struct toshiba_acpi_dev*) ; 
 int /*<<< orphan*/  toshiba_attr_group ; 
 int /*<<< orphan*/  wmi_has_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshiba_acpi_notify(struct acpi_device *acpi_dev, u32 event)
{
	struct toshiba_acpi_dev *dev = acpi_driver_data(acpi_dev);

	switch (event) {
	case 0x80: /* Hotkeys and some system events */
		/*
		 * Machines with this WMI GUID aren't supported due to bugs in
		 * their AML.
		 *
		 * Return silently to avoid triggering a netlink event.
		 */
		if (wmi_has_guid(TOSHIBA_WMI_EVENT_GUID))
			return;
		toshiba_acpi_process_hotkeys(dev);
		break;
	case 0x81: /* Dock events */
	case 0x82:
	case 0x83:
		pr_info("Dock event received %x\n", event);
		break;
	case 0x88: /* Thermal events */
		pr_info("Thermal event received\n");
		break;
	case 0x8f: /* LID closed */
	case 0x90: /* LID is closed and Dock has been ejected */
		break;
	case 0x8c: /* SATA power events */
	case 0x8b:
		pr_info("SATA power event received %x\n", event);
		break;
	case 0x92: /* Keyboard backlight mode changed */
		dev->kbd_event_generated = true;
		/* Update sysfs entries */
		if (sysfs_update_group(&acpi_dev->dev.kobj,
				       &toshiba_attr_group))
			pr_err("Unable to update sysfs entries\n");
		/* Notify LED subsystem about keyboard backlight change */
		if (dev->kbd_type == 2 && dev->kbd_mode != SCI_KBD_MODE_AUTO)
			led_classdev_notify_brightness_hw_changed(&dev->kbd_led,
					(dev->kbd_mode == SCI_KBD_MODE_ON) ?
					LED_FULL : LED_OFF);
		break;
	case 0x85: /* Unknown */
	case 0x8d: /* Unknown */
	case 0x8e: /* Unknown */
	case 0x94: /* Unknown */
	case 0x95: /* Unknown */
	default:
		pr_info("Unknown event received %x\n", event);
		break;
	}

	acpi_bus_generate_netlink_event(acpi_dev->pnp.device_class,
					dev_name(&acpi_dev->dev),
					event, (event == 0x80) ?
					dev->last_key_event : 0);
}