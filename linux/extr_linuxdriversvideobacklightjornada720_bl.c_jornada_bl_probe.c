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
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  BL_DEF_BRIGHT ; 
 int /*<<< orphan*/  BL_MAX_BRIGHT ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  S1D_DEVICENAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  jornada_bl_ops ; 
 int /*<<< orphan*/  jornada_bl_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int jornada_bl_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	int ret;
	struct backlight_device *bd;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = BL_MAX_BRIGHT;

	bd = devm_backlight_device_register(&pdev->dev, S1D_DEVICENAME,
					&pdev->dev, NULL, &jornada_bl_ops,
					&props);
	if (IS_ERR(bd)) {
		ret = PTR_ERR(bd);
		dev_err(&pdev->dev, "failed to register device, err=%x\n", ret);
		return ret;
	}

	bd->props.power = FB_BLANK_UNBLANK;
	bd->props.brightness = BL_DEF_BRIGHT;
	/*
	 * note. make sure max brightness is set otherwise
	 * you will get seemingly non-related errors when
	 * trying to change brightness
	 */
	jornada_bl_update_status(bd);

	platform_set_drvdata(pdev, bd);
	dev_info(&pdev->dev, "HP Jornada 700 series backlight driver\n");

	return 0;
}