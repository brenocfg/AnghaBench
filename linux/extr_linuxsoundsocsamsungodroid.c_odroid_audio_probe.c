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
struct snd_soc_dai_link {int dai_fmt; char* name; char* stream_name; scalar_t__ cpu_of_node; scalar_t__ platform_of_node; int /*<<< orphan*/ * ops; } ;
struct snd_soc_card {int fully_routed; int num_links; struct snd_soc_dai_link* dai_link; int /*<<< orphan*/  owner; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct odroid_priv {void* sclk_i2s; void* clk_i2s_bus; struct snd_soc_dai_link dai_link; struct snd_soc_card card; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct odroid_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  odroid_card_ops ; 
 void* of_clk_get_by_name (scalar_t__,char*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 scalar_t__ of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct odroid_priv*) ; 
 int snd_soc_of_get_dai_link_codecs (struct device*,struct device_node*,struct snd_soc_dai_link*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_audio_simple_widgets (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  snd_soc_of_put_dai_link_codecs (struct snd_soc_dai_link*) ; 

__attribute__((used)) static int odroid_audio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *cpu, *codec;
	struct odroid_priv *priv;
	struct snd_soc_dai_link *link;
	struct snd_soc_card *card;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	card = &priv->card;
	card->dev = dev;

	card->owner = THIS_MODULE;
	card->fully_routed = true;

	snd_soc_card_set_drvdata(card, priv);

	ret = snd_soc_of_parse_card_name(card, "model");
	if (ret < 0)
		return ret;

	if (of_property_read_bool(dev->of_node, "samsung,audio-widgets")) {
		ret = snd_soc_of_parse_audio_simple_widgets(card,
						"samsung,audio-widgets");
		if (ret < 0)
			return ret;
	}

	if (of_property_read_bool(dev->of_node, "samsung,audio-routing")) {
		ret = snd_soc_of_parse_audio_routing(card,
						"samsung,audio-routing");
		if (ret < 0)
			return ret;
	}

	link = &priv->dai_link;

	link->ops = &odroid_card_ops;
	link->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS;

	card->dai_link = &priv->dai_link;
	card->num_links = 1;

	cpu = of_get_child_by_name(dev->of_node, "cpu");
	codec = of_get_child_by_name(dev->of_node, "codec");

	link->cpu_of_node = of_parse_phandle(cpu, "sound-dai", 0);
	if (!link->cpu_of_node) {
		dev_err(dev, "Failed parsing cpu/sound-dai property\n");
		return -EINVAL;
	}

	ret = snd_soc_of_get_dai_link_codecs(dev, codec, link);
	if (ret < 0)
		goto err_put_codec_n;

	link->platform_of_node = link->cpu_of_node;

	link->name = "Primary";
	link->stream_name = link->name;


	priv->sclk_i2s = of_clk_get_by_name(link->cpu_of_node, "i2s_opclk1");
	if (IS_ERR(priv->sclk_i2s)) {
		ret = PTR_ERR(priv->sclk_i2s);
		goto err_put_i2s_n;
	}

	priv->clk_i2s_bus = of_clk_get_by_name(link->cpu_of_node, "iis");
	if (IS_ERR(priv->clk_i2s_bus)) {
		ret = PTR_ERR(priv->clk_i2s_bus);
		goto err_put_sclk;
	}

	ret = devm_snd_soc_register_card(dev, card);
	if (ret < 0) {
		dev_err(dev, "snd_soc_register_card() failed: %d\n", ret);
		goto err_put_clk_i2s;
	}

	return 0;

err_put_clk_i2s:
	clk_put(priv->clk_i2s_bus);
err_put_sclk:
	clk_put(priv->sclk_i2s);
err_put_i2s_n:
	of_node_put(link->cpu_of_node);
err_put_codec_n:
	snd_soc_of_put_dai_link_codecs(link);
	return ret;
}