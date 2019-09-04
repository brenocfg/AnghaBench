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
struct device {int dummy; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* acer_backlight_device ; 
 int /*<<< orphan*/  acer_bl_ops ; 
 struct backlight_device* backlight_device_register (char*,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  max_brightness ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  read_brightness (struct backlight_device*) ; 

__attribute__((used)) static int acer_backlight_init(struct device *dev)
{
	struct backlight_properties props;
	struct backlight_device *bd;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max_brightness;
	bd = backlight_device_register("acer-wmi", dev, NULL, &acer_bl_ops,
				       &props);
	if (IS_ERR(bd)) {
		pr_err("Could not register Acer backlight device\n");
		acer_backlight_device = NULL;
		return PTR_ERR(bd);
	}

	acer_backlight_device = bd;

	bd->props.power = FB_BLANK_UNBLANK;
	bd->props.brightness = read_brightness(bd);
	backlight_update_status(bd);
	return 0;
}