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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ad1836_priv {size_t type; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {size_t driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1836_regmap_config ; 
 int /*<<< orphan*/ * ad183x_dais ; 
 struct ad1836_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_ad1836 ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ad1836_priv*) ; 

__attribute__((used)) static int ad1836_spi_probe(struct spi_device *spi)
{
	struct ad1836_priv *ad1836;
	int ret;

	ad1836 = devm_kzalloc(&spi->dev, sizeof(struct ad1836_priv),
			      GFP_KERNEL);
	if (ad1836 == NULL)
		return -ENOMEM;

	ad1836->regmap = devm_regmap_init_spi(spi, &ad1836_regmap_config);
	if (IS_ERR(ad1836->regmap))
		return PTR_ERR(ad1836->regmap);

	ad1836->type = spi_get_device_id(spi)->driver_data;

	spi_set_drvdata(spi, ad1836);

	ret = devm_snd_soc_register_component(&spi->dev,
			&soc_component_dev_ad1836, &ad183x_dais[ad1836->type], 1);
	return ret;
}