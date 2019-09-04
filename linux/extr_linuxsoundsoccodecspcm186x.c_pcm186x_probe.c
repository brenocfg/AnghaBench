#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct pcm186x_priv {TYPE_1__* supplies; struct regmap* regmap; } ;
struct device {int dummy; } ;
typedef  enum pcm186x_type { ____Placeholder_pcm186x_type } pcm186x_type ;
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PCM1862 131 
#define  PCM1863 130 
#define  PCM1864 129 
#define  PCM1865 128 
 int /*<<< orphan*/  PCM186X_PAGE ; 
 int /*<<< orphan*/  PCM186X_RESET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pcm186x_priv*) ; 
 struct pcm186x_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcm1863_dai ; 
 int /*<<< orphan*/  pcm1865_dai ; 
 int /*<<< orphan*/ * pcm186x_supply_names ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_codec_dev_pcm1863 ; 
 int /*<<< orphan*/  soc_codec_dev_pcm1865 ; 

int pcm186x_probe(struct device *dev, enum pcm186x_type type, int irq,
		  struct regmap *regmap)
{
	struct pcm186x_priv *priv;
	int i, ret;

	priv = devm_kzalloc(dev, sizeof(struct pcm186x_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(dev, priv);
	priv->regmap = regmap;

	for (i = 0; i < ARRAY_SIZE(priv->supplies); i++)
		priv->supplies[i].supply = pcm186x_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(priv->supplies),
				      priv->supplies);
	if (ret) {
		dev_err(dev, "failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies),
				    priv->supplies);
	if (ret) {
		dev_err(dev, "failed enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset device registers for a consistent power-on like state */
	ret = regmap_write(regmap, PCM186X_PAGE, PCM186X_RESET);
	if (ret) {
		dev_err(dev, "failed to write device: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				     priv->supplies);
	if (ret) {
		dev_err(dev, "failed disable supplies: %d\n", ret);
		return ret;
	}

	switch (type) {
	case PCM1865:
	case PCM1864:
		ret = devm_snd_soc_register_component(dev, &soc_codec_dev_pcm1865,
					     &pcm1865_dai, 1);
		break;
	case PCM1863:
	case PCM1862:
	default:
		ret = devm_snd_soc_register_component(dev, &soc_codec_dev_pcm1863,
					     &pcm1863_dai, 1);
	}
	if (ret) {
		dev_err(dev, "failed to register CODEC: %d\n", ret);
		return ret;
	}

	return 0;
}