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
struct spi_device_id {int /*<<< orphan*/  driver_data; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct regmap_config {int val_bits; int reg_bits; int read_flag_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int adau1781_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap_config adau1781_regmap_config ; 
 int /*<<< orphan*/  adau1781_spi_switch_mode ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,struct regmap_config*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int adau1781_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct regmap_config config;

	if (!id)
		return -EINVAL;

	config = adau1781_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 24;
	config.read_flag_mask = 0x1;

	return adau1781_probe(&spi->dev,
		devm_regmap_init_spi(spi, &config),
		id->driver_data, adau1781_spi_switch_mode);
}