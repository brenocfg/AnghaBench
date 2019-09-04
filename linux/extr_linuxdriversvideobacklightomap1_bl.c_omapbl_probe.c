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
struct omap_backlight_config {int /*<<< orphan*/  default_intensity; } ;
struct omap_backlight {int /*<<< orphan*/ * dev; struct omap_backlight_config* pdata; scalar_t__ current_intensity; int /*<<< orphan*/  powermode; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  OMAPBL_MAX_INTENSITY ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  PWL ; 
 struct omap_backlight_config* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct omap_backlight*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct omap_backlight* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapbl_ops ; 
 int /*<<< orphan*/  omapbl_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omapbl_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct backlight_device *dev;
	struct omap_backlight *bl;
	struct omap_backlight_config *pdata = dev_get_platdata(&pdev->dev);

	if (!pdata)
		return -ENXIO;

	bl = devm_kzalloc(&pdev->dev, sizeof(struct omap_backlight),
			  GFP_KERNEL);
	if (unlikely(!bl))
		return -ENOMEM;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = OMAPBL_MAX_INTENSITY;
	dev = devm_backlight_device_register(&pdev->dev, "omap-bl", &pdev->dev,
					bl, &omapbl_ops, &props);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	bl->powermode = FB_BLANK_POWERDOWN;
	bl->current_intensity = 0;

	bl->pdata = pdata;
	bl->dev = &pdev->dev;

	platform_set_drvdata(pdev, dev);

	omap_cfg_reg(PWL);	/* Conflicts with UART3 */

	dev->props.fb_blank = FB_BLANK_UNBLANK;
	dev->props.brightness = pdata->default_intensity;
	omapbl_update_status(dev);

	dev_info(&pdev->dev, "OMAP LCD backlight initialised\n");

	return 0;
}