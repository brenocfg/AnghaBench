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
struct snd_soc_card {int num_links; int num_configs; int /*<<< orphan*/ * codec_conf; struct snd_soc_dai_link* dai_link; struct device* dev; int /*<<< orphan*/  owner; } ;
struct simple_card_data {int /*<<< orphan*/  codec_conf; struct snd_soc_dai_link* dai_link; struct asoc_simple_dai* dai_props; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct asoc_simple_dai {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  asoc_simple_card_clean_reference (struct snd_soc_card*) ; 
 int asoc_simple_card_parse_of (struct simple_card_data*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct simple_card_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 int of_get_child_count (struct device_node*) ; 
 struct snd_soc_card* simple_priv_to_card (struct simple_card_data*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct simple_card_data*) ; 

__attribute__((used)) static int asoc_simple_card_probe(struct platform_device *pdev)
{
	struct simple_card_data *priv;
	struct snd_soc_dai_link *dai_link;
	struct asoc_simple_dai *dai_props;
	struct snd_soc_card *card;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int num, ret;

	/* Allocate the private data */
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	num = of_get_child_count(np);

	dai_props = devm_kcalloc(dev, num, sizeof(*dai_props), GFP_KERNEL);
	dai_link  = devm_kcalloc(dev, num, sizeof(*dai_link), GFP_KERNEL);
	if (!dai_props || !dai_link)
		return -ENOMEM;

	priv->dai_props				= dai_props;
	priv->dai_link				= dai_link;

	/* Init snd_soc_card */
	card = simple_priv_to_card(priv);
	card->owner		= THIS_MODULE;
	card->dev		= dev;
	card->dai_link		= priv->dai_link;
	card->num_links		= num;
	card->codec_conf	= &priv->codec_conf;
	card->num_configs	= 1;

	ret = asoc_simple_card_parse_of(priv);
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