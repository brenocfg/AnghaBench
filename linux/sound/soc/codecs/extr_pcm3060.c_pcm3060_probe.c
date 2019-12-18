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
struct pcm3060_priv {int /*<<< orphan*/  regmap; scalar_t__ out_se; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM3060_REG64 ; 
 int /*<<< orphan*/  PCM3060_REG_MRST ; 
 int /*<<< orphan*/  PCM3060_REG_SE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct pcm3060_priv* dev_get_drvdata (struct device*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm3060_dai ; 
 int /*<<< orphan*/  pcm3060_parse_dt (scalar_t__,struct pcm3060_priv*) ; 
 int /*<<< orphan*/  pcm3060_soc_comp_driver ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcm3060_probe(struct device *dev)
{
	int rc;
	struct pcm3060_priv *priv = dev_get_drvdata(dev);

	/* soft reset */
	rc = regmap_update_bits(priv->regmap, PCM3060_REG64,
				PCM3060_REG_MRST, 0);
	if (rc) {
		dev_err(dev, "failed to reset component, rc=%d\n", rc);
		return rc;
	}

	if (dev->of_node)
		pcm3060_parse_dt(dev->of_node, priv);

	if (priv->out_se)
		regmap_update_bits(priv->regmap, PCM3060_REG64,
				   PCM3060_REG_SE, PCM3060_REG_SE);

	rc = devm_snd_soc_register_component(dev, &pcm3060_soc_comp_driver,
					     pcm3060_dai,
					     ARRAY_SIZE(pcm3060_dai));
	if (rc) {
		dev_err(dev, "failed to register component, rc=%d\n", rc);
		return rc;
	}

	return 0;
}