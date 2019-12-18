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
struct aic26 {int master; struct spi_device* spi; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic26_dai ; 
 int /*<<< orphan*/  aic26_regmap ; 
 int /*<<< orphan*/  aic26_soc_component_dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct aic26*) ; 
 struct aic26* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int aic26_spi_probe(struct spi_device *spi)
{
	struct aic26 *aic26;
	int ret;

	dev_dbg(&spi->dev, "probing tlv320aic26 spi device\n");

	/* Allocate driver data */
	aic26 = devm_kzalloc(&spi->dev, sizeof *aic26, GFP_KERNEL);
	if (!aic26)
		return -ENOMEM;

	aic26->regmap = devm_regmap_init_spi(spi, &aic26_regmap);
	if (IS_ERR(aic26->regmap))
		return PTR_ERR(aic26->regmap);

	/* Initialize the driver data */
	aic26->spi = spi;
	dev_set_drvdata(&spi->dev, aic26);
	aic26->master = 1;

	ret = devm_snd_soc_register_component(&spi->dev,
			&aic26_soc_component_dev, &aic26_dai, 1);
	return ret;
}