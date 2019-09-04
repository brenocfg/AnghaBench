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
struct eeepc_laptop {struct backlight_device* backlight_device; TYPE_1__* platform_device; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int /*<<< orphan*/  EEEPC_LAPTOP_FILE ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eeepc_laptop*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  eeepcbl_ops ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  read_brightness (struct backlight_device*) ; 

__attribute__((used)) static int eeepc_backlight_init(struct eeepc_laptop *eeepc)
{
	struct backlight_properties props;
	struct backlight_device *bd;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = 15;
	bd = backlight_device_register(EEEPC_LAPTOP_FILE,
				       &eeepc->platform_device->dev, eeepc,
				       &eeepcbl_ops, &props);
	if (IS_ERR(bd)) {
		pr_err("Could not register eeepc backlight device\n");
		eeepc->backlight_device = NULL;
		return PTR_ERR(bd);
	}
	eeepc->backlight_device = bd;
	bd->props.brightness = read_brightness(bd);
	bd->props.power = FB_BLANK_UNBLANK;
	backlight_update_status(bd);
	return 0;
}