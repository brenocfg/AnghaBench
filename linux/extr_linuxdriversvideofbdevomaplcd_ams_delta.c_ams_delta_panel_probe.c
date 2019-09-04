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
struct platform_device {int dummy; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_DEFAULT_CONTRAST ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  ams_delta_lcd_set_contrast (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_lcd_set_power (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_panel ; 
 int /*<<< orphan*/  omapfb_register_panel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ams_delta_panel_probe(struct platform_device *pdev)
{
	struct lcd_device *lcd_device = NULL;
#ifdef CONFIG_LCD_CLASS_DEVICE
	int ret;

	lcd_device = lcd_device_register("omapfb", &pdev->dev, NULL,
						&ams_delta_lcd_ops);

	if (IS_ERR(lcd_device)) {
		ret = PTR_ERR(lcd_device);
		dev_err(&pdev->dev, "failed to register device\n");
		return ret;
	}

	platform_set_drvdata(pdev, lcd_device);
	lcd_device->props.max_contrast = AMS_DELTA_MAX_CONTRAST;
#endif

	ams_delta_lcd_set_contrast(lcd_device, AMS_DELTA_DEFAULT_CONTRAST);
	ams_delta_lcd_set_power(lcd_device, FB_BLANK_UNBLANK);

	omapfb_register_panel(&ams_delta_panel);
	return 0;
}