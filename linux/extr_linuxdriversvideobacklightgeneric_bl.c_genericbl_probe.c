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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct generic_bl_info {int limit_mask; char* name; int /*<<< orphan*/  default_intensity; int /*<<< orphan*/  max_intensity; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct generic_bl_info* bl_machinfo ; 
 struct generic_bl_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct backlight_device* generic_backlight_device ; 
 int /*<<< orphan*/  genericbl_ops ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int genericbl_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct generic_bl_info *machinfo = dev_get_platdata(&pdev->dev);
	const char *name = "generic-bl";
	struct backlight_device *bd;

	bl_machinfo = machinfo;
	if (!machinfo->limit_mask)
		machinfo->limit_mask = -1;

	if (machinfo->name)
		name = machinfo->name;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = machinfo->max_intensity;
	bd = devm_backlight_device_register(&pdev->dev, name, &pdev->dev,
					NULL, &genericbl_ops, &props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	platform_set_drvdata(pdev, bd);

	bd->props.power = FB_BLANK_UNBLANK;
	bd->props.brightness = machinfo->default_intensity;
	backlight_update_status(bd);

	generic_backlight_device = bd;

	dev_info(&pdev->dev, "Generic Backlight Driver Initialized.\n");
	return 0;
}