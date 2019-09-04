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

/* Variables and functions */
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int es8328_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es8328_regmap_config ; 

__attribute__((used)) static int es8328_spi_probe(struct spi_device *spi)
{
	return es8328_probe(&spi->dev,
			devm_regmap_init_spi(spi, &es8328_regmap_config));
}