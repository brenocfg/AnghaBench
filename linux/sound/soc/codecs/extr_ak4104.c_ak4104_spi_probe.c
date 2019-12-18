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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct gpio_desc {int dummy; } ;
struct ak4104_private {struct gpio_desc* regmap; struct gpio_desc* regulator; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4104_REG_RESERVED ; 
 unsigned int AK4104_RESERVED_VAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  ak4104_dai ; 
 int /*<<< orphan*/  ak4104_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ak4104_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct gpio_desc* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int regmap_read (struct gpio_desc*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  soc_component_device_ak4104 ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ak4104_private*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ak4104_spi_probe(struct spi_device *spi)
{
	struct ak4104_private *ak4104;
	struct gpio_desc *reset_gpiod;
	unsigned int val;
	int ret;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	ak4104 = devm_kzalloc(&spi->dev, sizeof(struct ak4104_private),
			      GFP_KERNEL);
	if (ak4104 == NULL)
		return -ENOMEM;

	ak4104->regulator = devm_regulator_get(&spi->dev, "vdd");
	if (IS_ERR(ak4104->regulator)) {
		ret = PTR_ERR(ak4104->regulator);
		dev_err(&spi->dev, "Unable to get Vdd regulator: %d\n", ret);
		return ret;
	}

	ak4104->regmap = devm_regmap_init_spi(spi, &ak4104_regmap);
	if (IS_ERR(ak4104->regmap)) {
		ret = PTR_ERR(ak4104->regmap);
		return ret;
	}

	reset_gpiod = devm_gpiod_get_optional(&spi->dev, "reset",
					      GPIOD_OUT_HIGH);
	if (IS_ERR(reset_gpiod) &&
	    PTR_ERR(reset_gpiod) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	/* read the 'reserved' register - according to the datasheet, it
	 * should contain 0x5b. Not a good way to verify the presence of
	 * the device, but there is no hardware ID register. */
	ret = regmap_read(ak4104->regmap, AK4104_REG_RESERVED, &val);
	if (ret != 0)
		return ret;
	if (val != AK4104_RESERVED_VAL)
		return -ENODEV;

	spi_set_drvdata(spi, ak4104);

	ret = devm_snd_soc_register_component(&spi->dev,
			&soc_component_device_ak4104, &ak4104_dai, 1);
	return ret;
}