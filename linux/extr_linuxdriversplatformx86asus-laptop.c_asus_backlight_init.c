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
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
struct asus_laptop {struct backlight_device* backlight_device; TYPE_1__* platform_device; int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_LAPTOP_FILE ; 
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  METHOD_BRIGHTNESS_GET ; 
 int /*<<< orphan*/  METHOD_BRIGHTNESS_SET ; 
 int PTR_ERR (struct backlight_device*) ; 
 scalar_t__ acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_read_brightness (struct backlight_device*) ; 
 int /*<<< orphan*/  asusbl_ops ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct asus_laptop*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int asus_backlight_init(struct asus_laptop *asus)
{
	struct backlight_device *bd;
	struct backlight_properties props;

	if (acpi_check_handle(asus->handle, METHOD_BRIGHTNESS_GET, NULL) ||
	    acpi_check_handle(asus->handle, METHOD_BRIGHTNESS_SET, NULL))
		return 0;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.max_brightness = 15;
	props.type = BACKLIGHT_PLATFORM;

	bd = backlight_device_register(ASUS_LAPTOP_FILE,
				       &asus->platform_device->dev, asus,
				       &asusbl_ops, &props);
	if (IS_ERR(bd)) {
		pr_err("Could not register asus backlight device\n");
		asus->backlight_device = NULL;
		return PTR_ERR(bd);
	}

	asus->backlight_device = bd;
	bd->props.brightness = asus_read_brightness(bd);
	bd->props.power = FB_BLANK_UNBLANK;
	backlight_update_status(bd);
	return 0;
}