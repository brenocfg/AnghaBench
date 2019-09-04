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
struct snd_soc_dai_link {int dummy; } ;
struct snd_soc_card {int num_links; int /*<<< orphan*/  probe; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; struct snd_soc_dai_link* dai_link; struct device* dev; int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct graph_dai_props {int dummy; } ;
struct graph_card_data {struct snd_soc_dai_link* dai_link; struct graph_dai_props* dai_props; int /*<<< orphan*/  pa_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  asoc_graph_card_dapm_widgets ; 
 int asoc_graph_card_parse_of (struct graph_card_data*) ; 
 int asoc_graph_get_dais_count (struct device*) ; 
 int /*<<< orphan*/  asoc_graph_soc_card_probe ; 
 int /*<<< orphan*/  asoc_simple_card_clean_reference (struct snd_soc_card*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct graph_card_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 struct snd_soc_card* graph_priv_to_card (struct graph_card_data*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct graph_card_data*) ; 

__attribute__((used)) static int asoc_graph_card_probe(struct platform_device *pdev)
{
	struct graph_card_data *priv;
	struct snd_soc_dai_link *dai_link;
	struct graph_dai_props *dai_props;
	struct device *dev = &pdev->dev;
	struct snd_soc_card *card;
	int num, ret;

	/* Allocate the private data and the DAI link array */
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	num = asoc_graph_get_dais_count(dev);
	if (num == 0)
		return -EINVAL;

	dai_props = devm_kcalloc(dev, num, sizeof(*dai_props), GFP_KERNEL);
	dai_link  = devm_kcalloc(dev, num, sizeof(*dai_link), GFP_KERNEL);
	if (!dai_props || !dai_link)
		return -ENOMEM;

	priv->pa_gpio = devm_gpiod_get_optional(dev, "pa", GPIOD_OUT_LOW);
	if (IS_ERR(priv->pa_gpio)) {
		ret = PTR_ERR(priv->pa_gpio);
		dev_err(dev, "failed to get amplifier gpio: %d\n", ret);
		return ret;
	}

	priv->dai_props			= dai_props;
	priv->dai_link			= dai_link;

	/* Init snd_soc_card */
	card = graph_priv_to_card(priv);
	card->owner	= THIS_MODULE;
	card->dev	= dev;
	card->dai_link	= dai_link;
	card->num_links	= num;
	card->dapm_widgets = asoc_graph_card_dapm_widgets;
	card->num_dapm_widgets = ARRAY_SIZE(asoc_graph_card_dapm_widgets);
	card->probe	= asoc_graph_soc_card_probe;

	ret = asoc_graph_card_parse_of(priv);
	if (ret < 0) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "parse error %d\n", ret);
		goto err;
	}

	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_register_card(dev, card);
	if (ret < 0)
		goto err;

	return 0;
err:
	asoc_simple_card_clean_reference(card);

	return ret;
}