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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ltv350qv {struct lcd_device* ld; void* buffer; int /*<<< orphan*/  power; struct spi_device* spi; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct ltv350qv*,int /*<<< orphan*/ *) ; 
 int ltv350qv_power (struct ltv350qv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltv_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ltv350qv*) ; 

__attribute__((used)) static int ltv350qv_probe(struct spi_device *spi)
{
	struct ltv350qv *lcd;
	struct lcd_device *ld;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(struct ltv350qv), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	lcd->spi = spi;
	lcd->power = FB_BLANK_POWERDOWN;
	lcd->buffer = devm_kzalloc(&spi->dev, 8, GFP_KERNEL);
	if (!lcd->buffer)
		return -ENOMEM;

	ld = devm_lcd_device_register(&spi->dev, "ltv350qv", &spi->dev, lcd,
					&ltv_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	lcd->ld = ld;

	ret = ltv350qv_power(lcd, FB_BLANK_UNBLANK);
	if (ret)
		return ret;

	spi_set_drvdata(spi, lcd);

	return 0;
}