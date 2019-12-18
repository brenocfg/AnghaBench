#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {int num_codecs; int dpcm_capture; TYPE_1__* cpus; } ;
struct snd_soc_card {int fully_routed; struct snd_soc_dai_link* dai_link; void* num_links; void* num_dapm_routes; void* dapm_routes; int /*<<< orphan*/  owner; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_phandle_args {struct device_node* np; } ;
struct odroid_priv {void* sclk_i2s; void* clk_i2s_bus; int /*<<< orphan*/  lock; struct snd_soc_card card; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dai_name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct odroid_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 void* odroid_card_dais ; 
 void* odroid_dapm_routes ; 
 void* of_clk_get_by_name (struct device_node*,char*) ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct odroid_priv*) ; 
 int snd_soc_get_dai_name (struct of_phandle_args*,int /*<<< orphan*/ *) ; 
 int snd_soc_of_get_dai_link_codecs (struct device*,struct device_node*,struct snd_soc_dai_link*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_audio_simple_widgets (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  snd_soc_of_put_dai_link_codecs (struct snd_soc_dai_link*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int odroid_audio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *cpu_dai = NULL;
	struct device_node *cpu, *codec;
	struct odroid_priv *priv;
	struct snd_soc_card *card;
	struct snd_soc_dai_link *link, *codec_link;
	int num_pcms, ret, i;
	struct of_phandle_args args = {};

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	card = &priv->card;
	card->dev = dev;

	card->owner = THIS_MODULE;
	card->fully_routed = true;

	spin_lock_init(&priv->lock);
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

	card->dai_link = odroid_card_dais;
	card->num_links = ARRAY_SIZE(odroid_card_dais);

	cpu = of_get_child_by_name(dev->of_node, "cpu");
	codec = of_get_child_by_name(dev->of_node, "codec");
	link = card->dai_link;
	codec_link = &card->dai_link[1];

	/*
	 * For backwards compatibility create the secondary CPU DAI link only
	 * if there are 2 CPU DAI entries in the cpu sound-dai property in DT.
	 * Also add required DAPM routes not available in old DTS.
	 */
	num_pcms = of_count_phandle_with_args(cpu, "sound-dai",
					      "#sound-dai-cells");
	if (num_pcms == 1) {
		card->dapm_routes = odroid_dapm_routes;
		card->num_dapm_routes = ARRAY_SIZE(odroid_dapm_routes);
		card->num_links--;
	}

	for (i = 0; i < num_pcms; i++, link += 2) {
		ret = of_parse_phandle_with_args(cpu, "sound-dai",
						 "#sound-dai-cells", i, &args);
		if (ret < 0)
			break;

		if (!args.np) {
			dev_err(dev, "sound-dai property parse error: %d\n", ret);
			ret = -EINVAL;
			break;
		}

		ret = snd_soc_get_dai_name(&args, &link->cpus->dai_name);
		of_node_put(args.np);

		if (ret < 0)
			break;
	}
	if (ret == 0) {
		cpu_dai = of_parse_phandle(cpu, "sound-dai", 0);
		if (!cpu_dai)
			ret = -EINVAL;
	}

	of_node_put(cpu);
	if (ret < 0)
		goto err_put_node;

	ret = snd_soc_of_get_dai_link_codecs(dev, codec, codec_link);
	if (ret < 0)
		goto err_put_cpu_dai;

	/* Set capture capability only for boards with the MAX98090 CODEC */
	if (codec_link->num_codecs > 1) {
		card->dai_link[0].dpcm_capture = 1;
		card->dai_link[1].dpcm_capture = 1;
	}

	priv->sclk_i2s = of_clk_get_by_name(cpu_dai, "i2s_opclk1");
	if (IS_ERR(priv->sclk_i2s)) {
		ret = PTR_ERR(priv->sclk_i2s);
		goto err_put_cpu_dai;
	}

	priv->clk_i2s_bus = of_clk_get_by_name(cpu_dai, "iis");
	if (IS_ERR(priv->clk_i2s_bus)) {
		ret = PTR_ERR(priv->clk_i2s_bus);
		goto err_put_sclk;
	}

	ret = devm_snd_soc_register_card(dev, card);
	if (ret < 0) {
		dev_err(dev, "snd_soc_register_card() failed: %d\n", ret);
		goto err_put_clk_i2s;
	}

	of_node_put(cpu_dai);
	of_node_put(codec);
	return 0;

err_put_clk_i2s:
	clk_put(priv->clk_i2s_bus);
err_put_sclk:
	clk_put(priv->sclk_i2s);
err_put_cpu_dai:
	of_node_put(cpu_dai);
	snd_soc_of_put_dai_link_codecs(codec_link);
err_put_node:
	of_node_put(codec);
	return ret;
}