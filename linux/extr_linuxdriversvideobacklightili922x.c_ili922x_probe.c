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
typedef  int u16 ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  max_speed_hz; } ;
struct lcd_device {int dummy; } ;
struct ili922x {struct lcd_device* ld; int /*<<< orphan*/  power; struct spi_device* spi; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ILITEK_DEVICE_ID ; 
 int ILITEK_DEVICE_ID_MASK ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  REG_DRIVER_CODE_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ili922x* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct ili922x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ili922x_display_init (struct spi_device*) ; 
 int /*<<< orphan*/  ili922x_lcd_power (struct ili922x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ili922x_ops ; 
 int ili922x_read (struct spi_device*,int /*<<< orphan*/ ,int*) ; 
 int ili922x_read_status (struct spi_device*,int*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ili922x*) ; 

__attribute__((used)) static int ili922x_probe(struct spi_device *spi)
{
	struct ili922x *ili;
	struct lcd_device *lcd;
	int ret;
	u16 reg = 0;

	ili = devm_kzalloc(&spi->dev, sizeof(*ili), GFP_KERNEL);
	if (!ili)
		return -ENOMEM;

	ili->spi = spi;
	spi_set_drvdata(spi, ili);

	/* check if the device is connected */
	ret = ili922x_read(spi, REG_DRIVER_CODE_READ, &reg);
	if (ret || ((reg & ILITEK_DEVICE_ID_MASK) != ILITEK_DEVICE_ID)) {
		dev_err(&spi->dev,
			"no LCD found: Chip ID 0x%x, ret %d\n",
			reg, ret);
		return -ENODEV;
	}

	dev_info(&spi->dev, "ILI%x found, SPI freq %d, mode %d\n",
		 reg, spi->max_speed_hz, spi->mode);

	ret = ili922x_read_status(spi, &reg);
	if (ret) {
		dev_err(&spi->dev, "reading RS failed...\n");
		return ret;
	}

	dev_dbg(&spi->dev, "status: 0x%x\n", reg);

	ili922x_display_init(spi);

	ili->power = FB_BLANK_POWERDOWN;

	lcd = devm_lcd_device_register(&spi->dev, "ili922xlcd", &spi->dev, ili,
					&ili922x_ops);
	if (IS_ERR(lcd)) {
		dev_err(&spi->dev, "cannot register LCD\n");
		return PTR_ERR(lcd);
	}

	ili->ld = lcd;
	spi_set_drvdata(spi, ili);

	ili922x_lcd_power(ili, FB_BLANK_UNBLANK);

	return 0;
}