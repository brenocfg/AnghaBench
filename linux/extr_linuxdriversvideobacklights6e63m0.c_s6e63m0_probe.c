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
struct s6e63m0 {int gamma_table_count; int /*<<< orphan*/  power; TYPE_2__* lcd_pd; struct lcd_device* bd; struct lcd_device* ld; int /*<<< orphan*/ * dev; struct spi_device* spi; } ;
struct TYPE_3__ {void* brightness; } ;
struct lcd_device {TYPE_1__ props; } ;
struct backlight_properties {void* max_brightness; int /*<<< orphan*/  type; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  gamma_table ;
struct TYPE_4__ {int /*<<< orphan*/  lcd_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 void* MAX_BRIGHTNESS ; 
 int MAX_GAMMA_LEVEL ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_attr_gamma_mode ; 
 int /*<<< orphan*/  dev_attr_gamma_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lcd_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct s6e63m0*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct s6e63m0* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct s6e63m0*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s6e63m0_backlight_ops ; 
 int /*<<< orphan*/  s6e63m0_lcd_ops ; 
 int /*<<< orphan*/  s6e63m0_power (struct s6e63m0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct s6e63m0*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int s6e63m0_probe(struct spi_device *spi)
{
	int ret = 0;
	struct s6e63m0 *lcd = NULL;
	struct lcd_device *ld = NULL;
	struct backlight_device *bd = NULL;
	struct backlight_properties props;

	lcd = devm_kzalloc(&spi->dev, sizeof(struct s6e63m0), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	/* s6e63m0 lcd panel uses 3-wire 9bits SPI Mode. */
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

	ld = devm_lcd_device_register(&spi->dev, "s6e63m0", &spi->dev, lcd,
				&s6e63m0_lcd_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	lcd->ld = ld;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;

	bd = devm_backlight_device_register(&spi->dev, "s6e63m0bl-bl",
					&spi->dev, lcd, &s6e63m0_backlight_ops,
					&props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	bd->props.brightness = MAX_BRIGHTNESS;
	lcd->bd = bd;

	/*
	 * it gets gamma table count available so it gets user
	 * know that.
	 */
	lcd->gamma_table_count =
	    sizeof(gamma_table) / (MAX_GAMMA_LEVEL * sizeof(int *));

	ret = device_create_file(&(spi->dev), &dev_attr_gamma_mode);
	if (ret < 0)
		dev_err(&(spi->dev), "failed to add sysfs entries\n");

	ret = device_create_file(&(spi->dev), &dev_attr_gamma_table);
	if (ret < 0)
		dev_err(&(spi->dev), "failed to add sysfs entries\n");

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

		s6e63m0_power(lcd, FB_BLANK_UNBLANK);
	} else {
		lcd->power = FB_BLANK_UNBLANK;
	}

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "s6e63m0 panel driver has been probed.\n");

	return 0;
}