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
struct platform_device {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct backlight_properties {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ max_brightness; int brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;
struct aat2870_bl_platform_data {scalar_t__ channels; scalar_t__ max_current; scalar_t__ max_brightness; } ;
struct aat2870_bl_driver_data {scalar_t__ channels; scalar_t__ max_current; scalar_t__ brightness; struct backlight_device* bd; struct platform_device* pdev; } ;

/* Variables and functions */
 scalar_t__ AAT2870_BL_CH_ALL ; 
 scalar_t__ AAT2870_CURRENT_27_9 ; 
 scalar_t__ AAT2870_ID_BL ; 
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  aat2870_bl_ops ; 
 int aat2870_bl_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct aat2870_bl_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct aat2870_bl_driver_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct aat2870_bl_driver_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct aat2870_bl_driver_data*) ; 

__attribute__((used)) static int aat2870_bl_probe(struct platform_device *pdev)
{
	struct aat2870_bl_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct aat2870_bl_driver_data *aat2870_bl;
	struct backlight_device *bd;
	struct backlight_properties props;
	int ret = 0;

	if (!pdata) {
		dev_err(&pdev->dev, "No platform data\n");
		ret = -ENXIO;
		goto out;
	}

	if (pdev->id != AAT2870_ID_BL) {
		dev_err(&pdev->dev, "Invalid device ID, %d\n", pdev->id);
		ret = -EINVAL;
		goto out;
	}

	aat2870_bl = devm_kzalloc(&pdev->dev,
				  sizeof(struct aat2870_bl_driver_data),
				  GFP_KERNEL);
	if (!aat2870_bl) {
		ret = -ENOMEM;
		goto out;
	}

	memset(&props, 0, sizeof(struct backlight_properties));

	props.type = BACKLIGHT_RAW;
	bd = devm_backlight_device_register(&pdev->dev, "aat2870-backlight",
					&pdev->dev, aat2870_bl, &aat2870_bl_ops,
					&props);
	if (IS_ERR(bd)) {
		dev_err(&pdev->dev,
			"Failed allocate memory for backlight device\n");
		ret = PTR_ERR(bd);
		goto out;
	}

	aat2870_bl->pdev = pdev;
	platform_set_drvdata(pdev, aat2870_bl);

	aat2870_bl->bd = bd;

	if (pdata->channels > 0)
		aat2870_bl->channels = pdata->channels;
	else
		aat2870_bl->channels = AAT2870_BL_CH_ALL;

	if (pdata->max_current > 0)
		aat2870_bl->max_current = pdata->max_current;
	else
		aat2870_bl->max_current = AAT2870_CURRENT_27_9;

	if (pdata->max_brightness > 0)
		bd->props.max_brightness = pdata->max_brightness;
	else
		bd->props.max_brightness = 255;

	aat2870_bl->brightness = 0;
	bd->props.power = FB_BLANK_UNBLANK;
	bd->props.brightness = bd->props.max_brightness;

	ret = aat2870_bl_update_status(bd);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to initialize\n");
		return ret;
	}

	return 0;

out:
	return ret;
}