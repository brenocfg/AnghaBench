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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int pcm179x_common_init (int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  pcm179x_regmap_config ; 

__attribute__((used)) static int pcm179x_spi_probe(struct spi_device *spi)
{
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_spi(spi, &pcm179x_regmap_config);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&spi->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	return pcm179x_common_init(&spi->dev, regmap);
}