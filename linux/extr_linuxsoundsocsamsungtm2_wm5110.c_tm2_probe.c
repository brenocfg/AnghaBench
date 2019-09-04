#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tm2_machine_priv {int /*<<< orphan*/  gpio_mic_bias; } ;
struct snd_soc_card {int num_links; TYPE_2__* aux_dev; TYPE_1__* dai_link; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_phandle_args {struct device_node* np; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* codec_of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  codec_dai_name; struct device_node* platform_of_node; struct device_node* cpu_of_node; struct device_node* codec_of_node; int /*<<< orphan*/ * platform_name; int /*<<< orphan*/ * cpu_name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tm2_machine_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int of_count_phandle_with_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 int of_parse_phandle_with_args (int /*<<< orphan*/ ,char*,char const*,int,struct of_phandle_args*) ; 
 int of_parse_phandle_with_fixed_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tm2_machine_priv*) ; 
 int snd_soc_get_dai_name (struct of_phandle_args*,int /*<<< orphan*/ *) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 struct snd_soc_card tm2_card ; 
 int /*<<< orphan*/  tm2_component ; 
 int /*<<< orphan*/  tm2_dai_links ; 
 int /*<<< orphan*/  tm2_ext_dai ; 

__attribute__((used)) static int tm2_probe(struct platform_device *pdev)
{
	struct device_node *cpu_dai_node[2] = {};
	struct device_node *codec_dai_node[2] = {};
	const char *cells_name = NULL;
	struct device *dev = &pdev->dev;
	struct snd_soc_card *card = &tm2_card;
	struct tm2_machine_priv *priv;
	struct of_phandle_args args;
	int num_codecs, ret, i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	snd_soc_card_set_drvdata(card, priv);
	card->dev = dev;

	priv->gpio_mic_bias = devm_gpiod_get(dev, "mic-bias", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->gpio_mic_bias)) {
		dev_err(dev, "Failed to get mic bias gpio\n");
		return PTR_ERR(priv->gpio_mic_bias);
	}

	ret = snd_soc_of_parse_card_name(card, "model");
	if (ret < 0) {
		dev_err(dev, "Card name is not specified\n");
		return ret;
	}

	ret = snd_soc_of_parse_audio_routing(card, "samsung,audio-routing");
	if (ret < 0) {
		dev_err(dev, "Audio routing is not specified or invalid\n");
		return ret;
	}

	card->aux_dev[0].codec_of_node = of_parse_phandle(dev->of_node,
							"audio-amplifier", 0);
	if (!card->aux_dev[0].codec_of_node) {
		dev_err(dev, "audio-amplifier property invalid or missing\n");
		return -EINVAL;
	}

	num_codecs = of_count_phandle_with_args(dev->of_node, "audio-codec",
						 NULL);

	/* Skip the HDMI link if not specified in DT */
	if (num_codecs > 1) {
		card->num_links = ARRAY_SIZE(tm2_dai_links);
		cells_name = "#sound-dai-cells";
	} else {
		card->num_links = ARRAY_SIZE(tm2_dai_links) - 1;
	}

	for (i = 0; i < num_codecs; i++) {
		struct of_phandle_args args;

		ret = of_parse_phandle_with_args(dev->of_node, "i2s-controller",
						 cells_name, i, &args);
		if (!args.np) {
			dev_err(dev, "i2s-controller property parse error: %d\n", i);
			ret = -EINVAL;
			goto dai_node_put;
		}
		cpu_dai_node[i] = args.np;

		codec_dai_node[i] = of_parse_phandle(dev->of_node,
						     "audio-codec", i);
		if (!codec_dai_node[i]) {
			dev_err(dev, "audio-codec property parse error\n");
			ret = -EINVAL;
			goto dai_node_put;
		}
	}

	/* Initialize WM5110 - I2S and HDMI - I2S1 DAI links */
	for (i = 0; i < card->num_links; i++) {
		unsigned int dai_index = 0; /* WM5110 */

		card->dai_link[i].cpu_name = NULL;
		card->dai_link[i].platform_name = NULL;

		if (num_codecs > 1 && i == card->num_links - 1)
			dai_index = 1; /* HDMI */

		card->dai_link[i].codec_of_node = codec_dai_node[dai_index];
		card->dai_link[i].cpu_of_node = cpu_dai_node[dai_index];
		card->dai_link[i].platform_of_node = cpu_dai_node[dai_index];
	}

	if (num_codecs > 1) {
		/* HDMI DAI link (I2S1) */
		i = card->num_links - 1;

		ret = of_parse_phandle_with_fixed_args(dev->of_node,
						"audio-codec", 0, 1, &args);
		if (ret) {
			dev_err(dev, "audio-codec property parse error\n");
			goto dai_node_put;
		}

		ret = snd_soc_get_dai_name(&args, &card->dai_link[i].codec_dai_name);
		if (ret) {
			dev_err(dev, "Unable to get codec_dai_name\n");
			goto dai_node_put;
		}
	}

	ret = devm_snd_soc_register_component(dev, &tm2_component,
				tm2_ext_dai, ARRAY_SIZE(tm2_ext_dai));
	if (ret < 0) {
		dev_err(dev, "Failed to register component: %d\n", ret);
		goto dai_node_put;
	}

	ret = devm_snd_soc_register_card(dev, card);
	if (ret < 0) {
		dev_err(dev, "Failed to register card: %d\n", ret);
		goto dai_node_put;
	}

dai_node_put:
	for (i = 0; i < num_codecs; i++) {
		of_node_put(codec_dai_node[i]);
		of_node_put(cpu_dai_node[i]);
	}

	of_node_put(card->aux_dev[0].codec_of_node);

	return ret;
}