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
struct pcm3060_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct pcm3060_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int pcm3060_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm3060_regmap ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct pcm3060_priv*) ; 

__attribute__((used)) static int pcm3060_spi_probe(struct spi_device *spi)
{
	struct pcm3060_priv *priv;

	priv = devm_kzalloc(&spi->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spi_set_drvdata(spi, priv);

	priv->regmap = devm_regmap_init_spi(spi, &pcm3060_regmap);
	if (IS_ERR(priv->regmap))
		return PTR_ERR(priv->regmap);

	return pcm3060_probe(&spi->dev);
}