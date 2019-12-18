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
struct snd_soc_card {int /*<<< orphan*/  probe; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; struct device* dev; int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct link_info {int /*<<< orphan*/  dais; int /*<<< orphan*/  link; } ;
struct asoc_simple_priv {int /*<<< orphan*/  pa_gpio; } ;
typedef  int /*<<< orphan*/  li ;

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
 int /*<<< orphan*/  asoc_simple_clean_reference (struct snd_soc_card*) ; 
 int /*<<< orphan*/  asoc_simple_debug_info (struct asoc_simple_priv*) ; 
 int asoc_simple_init_priv (struct asoc_simple_priv*,struct link_info*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct asoc_simple_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  graph_card_probe ; 
 int /*<<< orphan*/  graph_dapm_widgets ; 
 int /*<<< orphan*/  graph_get_dais_count (struct asoc_simple_priv*,struct link_info*) ; 
 int graph_parse_of (struct asoc_simple_priv*) ; 
 int /*<<< orphan*/  memset (struct link_info*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_card* simple_priv_to_card (struct asoc_simple_priv*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct asoc_simple_priv*) ; 

__attribute__((used)) static int graph_probe(struct platform_device *pdev)
{
	struct asoc_simple_priv *priv;
	struct device *dev = &pdev->dev;
	struct snd_soc_card *card;
	struct link_info li;
	int ret;

	/* Allocate the private data and the DAI link array */
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	card = simple_priv_to_card(priv);
	card->owner		= THIS_MODULE;
	card->dev		= dev;
	card->dapm_widgets	= graph_dapm_widgets;
	card->num_dapm_widgets	= ARRAY_SIZE(graph_dapm_widgets);
	card->probe		= graph_card_probe;

	memset(&li, 0, sizeof(li));
	graph_get_dais_count(priv, &li);
	if (!li.link || !li.dais)
		return -EINVAL;

	ret = asoc_simple_init_priv(priv, &li);
	if (ret < 0)
		return ret;

	priv->pa_gpio = devm_gpiod_get_optional(dev, "pa", GPIOD_OUT_LOW);
	if (IS_ERR(priv->pa_gpio)) {
		ret = PTR_ERR(priv->pa_gpio);
		dev_err(dev, "failed to get amplifier gpio: %d\n", ret);
		return ret;
	}

	ret = graph_parse_of(priv);
	if (ret < 0) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "parse error %d\n", ret);
		goto err;
	}

	snd_soc_card_set_drvdata(card, priv);

	asoc_simple_debug_info(priv);

	ret = devm_snd_soc_register_card(dev, card);
	if (ret < 0)
		goto err;

	return 0;
err:
	asoc_simple_clean_reference(card);

	return ret;
}