#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {int dai_fmt; char* name; char* stream_name; TYPE_3__* cpus; TYPE_2__* platforms; TYPE_1__* codecs; int /*<<< orphan*/ * ops; void* num_platforms; void* num_codecs; void* num_cpus; } ;
struct snow_priv {int /*<<< orphan*/  clk_i2s_bus; struct snd_soc_dai_link dai_link; } ;
struct snd_soc_card {int num_links; struct device* dev; struct snd_soc_dai_link* dai_link; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct TYPE_4__ {char* dai_name; void* of_node; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct snow_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 void* links_codecs ; 
 void* links_cpus ; 
 void* links_platforms ; 
 int /*<<< orphan*/  of_clk_get_by_name (struct device_node*,char*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct snow_priv*) ; 
 int snd_soc_of_get_dai_link_codecs (struct device*,struct device_node*,struct snd_soc_dai_link*) ; 
 int /*<<< orphan*/  snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  snd_soc_of_put_dai_link_codecs (struct snd_soc_dai_link*) ; 
 int /*<<< orphan*/  snow_card_ops ; 
 struct snd_soc_card snow_snd ; 

__attribute__((used)) static int snow_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct snd_soc_card *card = &snow_snd;
	struct device_node *cpu, *codec;
	struct snd_soc_dai_link *link;
	struct snow_priv *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	link = &priv->dai_link;

	link->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS;

	link->name = "Primary";
	link->stream_name = link->name;

	link->cpus = links_cpus;
	link->num_cpus = ARRAY_SIZE(links_cpus);
	link->codecs = links_codecs;
	link->num_codecs = ARRAY_SIZE(links_codecs);
	link->platforms = links_platforms;
	link->num_platforms = ARRAY_SIZE(links_platforms);

	card->dai_link = link;
	card->num_links = 1;
	card->dev = dev;

	/* Try new DT bindings with HDMI support first. */
	cpu = of_get_child_by_name(dev->of_node, "cpu");

	if (cpu) {
		link->ops = &snow_card_ops;

		link->cpus->of_node = of_parse_phandle(cpu, "sound-dai", 0);
		of_node_put(cpu);

		if (!link->cpus->of_node) {
			dev_err(dev, "Failed parsing cpu/sound-dai property\n");
			return -EINVAL;
		}

		codec = of_get_child_by_name(dev->of_node, "codec");
		ret = snd_soc_of_get_dai_link_codecs(dev, codec, link);
		of_node_put(codec);

		if (ret < 0) {
			of_node_put(link->cpus->of_node);
			dev_err(dev, "Failed parsing codec node\n");
			return ret;
		}

		priv->clk_i2s_bus = of_clk_get_by_name(link->cpus->of_node,
						       "i2s_opclk0");
		if (IS_ERR(priv->clk_i2s_bus)) {
			snd_soc_of_put_dai_link_codecs(link);
			of_node_put(link->cpus->of_node);
			return PTR_ERR(priv->clk_i2s_bus);
		}
	} else {
		link->codecs->dai_name = "HiFi",

		link->cpus->of_node = of_parse_phandle(dev->of_node,
						"samsung,i2s-controller", 0);
		if (!link->cpus->of_node) {
			dev_err(dev, "i2s-controller property parse error\n");
			return -EINVAL;
		}

		link->codecs->of_node = of_parse_phandle(dev->of_node,
						"samsung,audio-codec", 0);
		if (!link->codecs->of_node) {
			of_node_put(link->cpus->of_node);
			dev_err(dev, "audio-codec property parse error\n");
			return -EINVAL;
		}
	}

	link->platforms->of_node = link->cpus->of_node;

	/* Update card-name if provided through DT, else use default name */
	snd_soc_of_parse_card_name(card, "samsung,model");

	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_register_card(dev, card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		return ret;
	}

	return ret;
}