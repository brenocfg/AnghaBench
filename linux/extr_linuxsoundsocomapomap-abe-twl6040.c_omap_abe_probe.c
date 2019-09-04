#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int fully_routed; int num_links; TYPE_1__* dai_link; void* num_dapm_routes; void* dapm_routes; void* num_dapm_widgets; void* dapm_widgets; int /*<<< orphan*/  owner; TYPE_2__* dev; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct abe_twl6040 {TYPE_1__* dai_links; int /*<<< orphan*/  mclk_freq; int /*<<< orphan*/  jack_detection; struct snd_soc_card card; } ;
struct TYPE_5__ {char* name; char* stream_name; char* codec_dai_name; char* codec_name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  init; struct device_node* platform_of_node; struct device_node* cpu_of_node; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* audio_map ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct abe_twl6040* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_2__*,struct snd_soc_card*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_abe_dmic_init ; 
 int /*<<< orphan*/  omap_abe_dmic_ops ; 
 int /*<<< orphan*/  omap_abe_ops ; 
 int /*<<< orphan*/  omap_abe_twl6040_init ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct abe_twl6040*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 scalar_t__ snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 void* twl6040_dapm_widgets ; 

__attribute__((used)) static int omap_abe_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct snd_soc_card *card;
	struct device_node *dai_node;
	struct abe_twl6040 *priv;
	int num_links = 0;
	int ret = 0;

	if (!node) {
		dev_err(&pdev->dev, "of node is missing.\n");
		return -ENODEV;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(struct abe_twl6040), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	card = &priv->card;
	card->dev = &pdev->dev;
	card->owner = THIS_MODULE;
	card->dapm_widgets = twl6040_dapm_widgets;
	card->num_dapm_widgets = ARRAY_SIZE(twl6040_dapm_widgets);
	card->dapm_routes = audio_map;
	card->num_dapm_routes = ARRAY_SIZE(audio_map);

	if (snd_soc_of_parse_card_name(card, "ti,model")) {
		dev_err(&pdev->dev, "Card name is not provided\n");
		return -ENODEV;
	}

	ret = snd_soc_of_parse_audio_routing(card, "ti,audio-routing");
	if (ret) {
		dev_err(&pdev->dev, "Error while parsing DAPM routing\n");
		return ret;
	}

	dai_node = of_parse_phandle(node, "ti,mcpdm", 0);
	if (!dai_node) {
		dev_err(&pdev->dev, "McPDM node is not provided\n");
		return -EINVAL;
	}

	priv->dai_links[0].name = "DMIC";
	priv->dai_links[0].stream_name = "TWL6040";
	priv->dai_links[0].cpu_of_node = dai_node;
	priv->dai_links[0].platform_of_node = dai_node;
	priv->dai_links[0].codec_dai_name = "twl6040-legacy";
	priv->dai_links[0].codec_name = "twl6040-codec";
	priv->dai_links[0].init = omap_abe_twl6040_init;
	priv->dai_links[0].ops = &omap_abe_ops;

	dai_node = of_parse_phandle(node, "ti,dmic", 0);
	if (dai_node) {
		num_links = 2;
		priv->dai_links[1].name = "TWL6040";
		priv->dai_links[1].stream_name = "DMIC Capture";
		priv->dai_links[1].cpu_of_node = dai_node;
		priv->dai_links[1].platform_of_node = dai_node;
		priv->dai_links[1].codec_dai_name = "dmic-hifi";
		priv->dai_links[1].codec_name = "dmic-codec";
		priv->dai_links[1].init = omap_abe_dmic_init;
		priv->dai_links[1].ops = &omap_abe_dmic_ops;
	} else {
		num_links = 1;
	}

	priv->jack_detection = of_property_read_bool(node, "ti,jack-detection");
	of_property_read_u32(node, "ti,mclk-freq", &priv->mclk_freq);
	if (!priv->mclk_freq) {
		dev_err(&pdev->dev, "MCLK frequency not provided\n");
		return -EINVAL;
	}

	card->fully_routed = 1;

	if (!priv->mclk_freq) {
		dev_err(&pdev->dev, "MCLK frequency missing\n");
		return -ENODEV;
	}

	card->dai_link = priv->dai_links;
	card->num_links = num_links;

	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret)
		dev_err(&pdev->dev, "devm_snd_soc_register_card() failed: %d\n",
			ret);

	return ret;
}