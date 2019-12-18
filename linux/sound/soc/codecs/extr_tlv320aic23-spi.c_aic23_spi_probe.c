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
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int spi_setup (struct spi_device*) ; 
 int tlv320aic23_probe (int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  tlv320aic23_regmap ; 

__attribute__((used)) static int aic23_spi_probe(struct spi_device *spi)
{
	int ret;
	struct regmap *regmap;

	dev_dbg(&spi->dev, "probing tlv320aic23 spi device\n");

	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	regmap = devm_regmap_init_spi(spi, &tlv320aic23_regmap);
	return tlv320aic23_probe(&spi->dev, regmap);
}