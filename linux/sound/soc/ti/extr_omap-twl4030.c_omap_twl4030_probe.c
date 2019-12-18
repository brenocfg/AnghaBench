#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int num_links; int fully_routed; scalar_t__ name; TYPE_4__* dev; } ;
struct property {int dummy; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct omap_twl4030 {int /*<<< orphan*/  jack_detect; } ;
struct omap_tw4030_pdata {int /*<<< orphan*/  jack_detect; int /*<<< orphan*/  voice_connected; scalar_t__ card_name; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_9__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {struct device_node* of_node; int /*<<< orphan*/ * dai_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct omap_tw4030_pdata* dev_get_platdata (TYPE_4__*) ; 
 struct omap_twl4030* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_4__*,struct snd_soc_card*) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_card omap_twl4030_card ; 
 TYPE_3__* omap_twl4030_dai_links ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct omap_twl4030*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 scalar_t__ snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 

__attribute__((used)) static int omap_twl4030_probe(struct platform_device *pdev)
{
	struct omap_tw4030_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *node = pdev->dev.of_node;
	struct snd_soc_card *card = &omap_twl4030_card;
	struct omap_twl4030 *priv;
	int ret = 0;

	card->dev = &pdev->dev;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct omap_twl4030), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	if (node) {
		struct device_node *dai_node;
		struct property *prop;

		if (snd_soc_of_parse_card_name(card, "ti,model")) {
			dev_err(&pdev->dev, "Card name is not provided\n");
			return -ENODEV;
		}

		dai_node = of_parse_phandle(node, "ti,mcbsp", 0);
		if (!dai_node) {
			dev_err(&pdev->dev, "McBSP node is not provided\n");
			return -EINVAL;
		}
		omap_twl4030_dai_links[0].cpus->dai_name  = NULL;
		omap_twl4030_dai_links[0].cpus->of_node = dai_node;

		omap_twl4030_dai_links[0].platforms->name  = NULL;
		omap_twl4030_dai_links[0].platforms->of_node = dai_node;

		dai_node = of_parse_phandle(node, "ti,mcbsp-voice", 0);
		if (!dai_node) {
			card->num_links = 1;
		} else {
			omap_twl4030_dai_links[1].cpus->dai_name  = NULL;
			omap_twl4030_dai_links[1].cpus->of_node = dai_node;

			omap_twl4030_dai_links[1].platforms->name  = NULL;
			omap_twl4030_dai_links[1].platforms->of_node = dai_node;
		}

		priv->jack_detect = of_get_named_gpio(node,
						      "ti,jack-det-gpio", 0);

		/* Optional: audio routing can be provided */
		prop = of_find_property(node, "ti,audio-routing", NULL);
		if (prop) {
			ret = snd_soc_of_parse_audio_routing(card,
							    "ti,audio-routing");
			if (ret)
				return ret;

			card->fully_routed = 1;
		}
	} else if (pdata) {
		if (pdata->card_name) {
			card->name = pdata->card_name;
		} else {
			dev_err(&pdev->dev, "Card name is not provided\n");
			return -ENODEV;
		}

		if (!pdata->voice_connected)
			card->num_links = 1;

		priv->jack_detect = pdata->jack_detect;
	} else {
		dev_err(&pdev->dev, "Missing pdata\n");
		return -ENODEV;
	}

	snd_soc_card_set_drvdata(card, priv);
	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret) {
		dev_err(&pdev->dev, "devm_snd_soc_register_card() failed: %d\n",
			ret);
		return ret;
	}

	return 0;
}