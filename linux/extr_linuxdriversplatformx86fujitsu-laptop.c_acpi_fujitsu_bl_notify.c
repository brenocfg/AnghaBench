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
typedef  int /*<<< orphan*/  u32 ;
struct fujitsu_bl {int brightness_level; int /*<<< orphan*/  input; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUJITSU_NOTIFY_CODE ; 
 struct fujitsu_bl* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  acpi_handle_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_brightness_adjust ; 
 int /*<<< orphan*/  get_lcd_level (struct acpi_device*) ; 
 int /*<<< orphan*/  set_lcd_level (struct acpi_device*,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void acpi_fujitsu_bl_notify(struct acpi_device *device, u32 event)
{
	struct fujitsu_bl *priv = acpi_driver_data(device);
	int oldb, newb;

	if (event != ACPI_FUJITSU_NOTIFY_CODE) {
		acpi_handle_info(device->handle, "unsupported event [0x%x]\n",
				 event);
		sparse_keymap_report_event(priv->input, -1, 1, true);
		return;
	}

	oldb = priv->brightness_level;
	get_lcd_level(device);
	newb = priv->brightness_level;

	acpi_handle_debug(device->handle,
			  "brightness button event [%i -> %i]\n", oldb, newb);

	if (oldb == newb)
		return;

	if (!disable_brightness_adjust)
		set_lcd_level(device, newb);

	sparse_keymap_report_event(priv->input, oldb < newb, 1, true);
}