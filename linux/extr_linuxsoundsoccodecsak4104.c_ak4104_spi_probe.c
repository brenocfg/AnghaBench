#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device_node* of_node; } ;
struct spi_device {int bits_per_word; TYPE_1__ dev; int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;
struct ak4104_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regulator; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int /*<<< orphan*/  AK4104_REG_RESERVED ; 
 unsigned int AK4104_RESERVED_VAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  ak4104_dai ; 
 int /*<<< orphan*/  ak4104_regmap ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int devm_gpio_request_one (TYPE_1__*,int,int /*<<< orphan*/ ,char*) ; 
 struct ak4104_private* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  soc_component_device_ak4104 ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ak4104_private*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ak4104_spi_probe(struct spi_device *spi)
{
	struct device_node *np = spi->dev.of_node;
	struct ak4104_private *ak4104;
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

	if (np) {
		enum of_gpio_flags flags;
		int gpio = of_get_named_gpio_flags(np, "reset-gpio", 0, &flags);

		if (gpio_is_valid(gpio)) {
			ret = devm_gpio_request_one(&spi->dev, gpio,
				     flags & OF_GPIO_ACTIVE_LOW ?
					GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH,
				     "ak4104 reset");
			if (ret < 0)
				return ret;
		}
	}

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