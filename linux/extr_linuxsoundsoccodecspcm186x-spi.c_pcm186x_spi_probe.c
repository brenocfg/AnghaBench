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
struct spi_device {int irq; int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;
typedef  enum pcm186x_type { ____Placeholder_pcm186x_type } pcm186x_type ;
struct TYPE_2__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int pcm186x_probe (int /*<<< orphan*/ *,int const,int,struct regmap*) ; 
 int /*<<< orphan*/  pcm186x_regmap ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int pcm186x_spi_probe(struct spi_device *spi)
{
	const enum pcm186x_type type =
			 (enum pcm186x_type)spi_get_device_id(spi)->driver_data;
	int irq = spi->irq;
	struct regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &pcm186x_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return pcm186x_probe(&spi->dev, type, irq, regmap);
}