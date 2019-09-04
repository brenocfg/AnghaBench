#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct corgi_lcd_platform_data {int /*<<< orphan*/  limit_mask; int /*<<< orphan*/  kick_battery; int /*<<< orphan*/  default_intensity; int /*<<< orphan*/  max_intensity; int /*<<< orphan*/  init_mode; } ;
struct corgi_lcd {int /*<<< orphan*/  limit_mask; TYPE_2__* bl_dev; TYPE_2__* lcd_dev; int /*<<< orphan*/  kick_battery; int /*<<< orphan*/  mode; int /*<<< orphan*/  power; struct spi_device* spi_dev; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  power; int /*<<< orphan*/  brightness; } ;
struct TYPE_9__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  CORGI_LCD_MODE_VGA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_2__*) ; 
 int /*<<< orphan*/  corgi_bl_ops ; 
 int /*<<< orphan*/  corgi_lcd_ops ; 
 int /*<<< orphan*/  corgi_lcd_set_power (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct corgi_lcd_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct corgi_lcd*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct corgi_lcd* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct corgi_lcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int setup_gpio_backlight (struct corgi_lcd*,struct corgi_lcd_platform_data*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct corgi_lcd*) ; 
 struct corgi_lcd* the_corgi_lcd ; 

__attribute__((used)) static int corgi_lcd_probe(struct spi_device *spi)
{
	struct backlight_properties props;
	struct corgi_lcd_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct corgi_lcd *lcd;
	int ret = 0;

	if (pdata == NULL) {
		dev_err(&spi->dev, "platform data not available\n");
		return -EINVAL;
	}

	lcd = devm_kzalloc(&spi->dev, sizeof(struct corgi_lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	lcd->spi_dev = spi;

	lcd->lcd_dev = devm_lcd_device_register(&spi->dev, "corgi_lcd",
						&spi->dev, lcd, &corgi_lcd_ops);
	if (IS_ERR(lcd->lcd_dev))
		return PTR_ERR(lcd->lcd_dev);

	lcd->power = FB_BLANK_POWERDOWN;
	lcd->mode = (pdata) ? pdata->init_mode : CORGI_LCD_MODE_VGA;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = pdata->max_intensity;
	lcd->bl_dev = devm_backlight_device_register(&spi->dev, "corgi_bl",
						&spi->dev, lcd, &corgi_bl_ops,
						&props);
	if (IS_ERR(lcd->bl_dev))
		return PTR_ERR(lcd->bl_dev);

	lcd->bl_dev->props.brightness = pdata->default_intensity;
	lcd->bl_dev->props.power = FB_BLANK_UNBLANK;

	ret = setup_gpio_backlight(lcd, pdata);
	if (ret)
		return ret;

	lcd->kick_battery = pdata->kick_battery;

	spi_set_drvdata(spi, lcd);
	corgi_lcd_set_power(lcd->lcd_dev, FB_BLANK_UNBLANK);
	backlight_update_status(lcd->bl_dev);

	lcd->limit_mask = pdata->limit_mask;
	the_corgi_lcd = lcd;
	return 0;
}