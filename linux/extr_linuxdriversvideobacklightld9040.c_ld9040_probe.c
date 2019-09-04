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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct ld9040 {int /*<<< orphan*/  power; TYPE_2__* lcd_pd; struct lcd_device* bd; struct lcd_device* ld; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct TYPE_3__ {void* brightness; } ;
struct lcd_device {TYPE_1__ props; } ;
struct backlight_properties {void* max_brightness; int /*<<< orphan*/  type; } ;
struct backlight_device {TYPE_1__ props; } ;
struct TYPE_4__ {int /*<<< orphan*/  lcd_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 void* MAX_BRIGHTNESS ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct lcd_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct ld9040*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct ld9040* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct ld9040*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld9040_backlight_ops ; 
 int /*<<< orphan*/  ld9040_lcd_ops ; 
 int /*<<< orphan*/  ld9040_power (struct ld9040*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ld9040*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  supplies ; 

__attribute__((used)) static int ld9040_probe(struct spi_device *spi)
{
	int ret = 0;
	struct ld9040 *lcd = NULL;
	struct lcd_device *ld = NULL;
	struct backlight_device *bd = NULL;
	struct backlight_properties props;

	lcd = devm_kzalloc(&spi->dev, sizeof(struct ld9040), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	/* ld9040 lcd panel uses 3-wire 9bits SPI Mode. */
	spi->bits_per_word = 9;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "spi setup failed.\n");
		return ret;
	}

	lcd->spi = spi;
	lcd->dev = &spi->dev;

	lcd->lcd_pd = dev_get_platdata(&spi->dev);
	if (!lcd->lcd_pd) {
		dev_err(&spi->dev, "platform data is NULL.\n");
		return -EINVAL;
	}

	mutex_init(&lcd->lock);

	ret = devm_regulator_bulk_get(lcd->dev, ARRAY_SIZE(supplies), supplies);
	if (ret) {
		dev_err(lcd->dev, "Failed to get regulators: %d\n", ret);
		return ret;
	}

	ld = devm_lcd_device_register(&spi->dev, "ld9040", &spi->dev, lcd,
					&ld9040_lcd_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	lcd->ld = ld;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;

	bd = devm_backlight_device_register(&spi->dev, "ld9040-bl", &spi->dev,
					lcd, &ld9040_backlight_ops, &props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	bd->props.brightness = MAX_BRIGHTNESS;
	lcd->bd = bd;

	/*
	 * if lcd panel was on from bootloader like u-boot then
	 * do not lcd on.
	 */
	if (!lcd->lcd_pd->lcd_enabled) {
		/*
		 * if lcd panel was off from bootloader then
		 * current lcd status is powerdown and then
		 * it enables lcd panel.
		 */
		lcd->power = FB_BLANK_POWERDOWN;

		ld9040_power(lcd, FB_BLANK_UNBLANK);
	} else {
		lcd->power = FB_BLANK_UNBLANK;
	}

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "ld9040 panel driver has been probed.\n");
	return 0;
}