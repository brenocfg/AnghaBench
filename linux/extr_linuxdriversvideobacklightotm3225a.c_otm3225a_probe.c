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
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct otm3225a_data {struct lcd_device* ld; struct spi_device* spi; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct otm3225a_data*) ; 
 struct otm3225a_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (struct device*,int /*<<< orphan*/ ,struct device*,struct otm3225a_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_enable_rgb_interface ; 
 int /*<<< orphan*/  display_init ; 
 int /*<<< orphan*/  otm3225a_ops ; 
 int /*<<< orphan*/  otm3225a_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otm3225a_probe(struct spi_device *spi)
{
	struct otm3225a_data *dd;
	struct lcd_device *ld;
	struct device *dev = &spi->dev;

	dd = devm_kzalloc(dev, sizeof(struct otm3225a_data), GFP_KERNEL);
	if (dd == NULL)
		return -ENOMEM;

	ld = devm_lcd_device_register(dev, dev_name(dev), dev, dd,
				      &otm3225a_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	dd->spi = spi;
	dd->ld = ld;
	dev_set_drvdata(dev, dd);

	dev_info(dev, "Initializing and switching to RGB interface");
	otm3225a_write(spi, display_init, ARRAY_SIZE(display_init));
	otm3225a_write(spi, display_enable_rgb_interface,
		       ARRAY_SIZE(display_enable_rgb_interface));
	return 0;
}