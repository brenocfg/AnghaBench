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
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int pcm512x_probe (int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  pcm512x_regmap ; 

__attribute__((used)) static int pcm512x_spi_probe(struct spi_device *spi)
{
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_spi(spi, &pcm512x_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		return ret;
	}

	return pcm512x_probe(&spi->dev, regmap);
}