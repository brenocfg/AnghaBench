#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; TYPE_5__* dev; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {TYPE_3__* platforms; TYPE_2__* cpus; TYPE_1__* codecs; } ;
struct TYPE_9__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {struct device_node* of_node; int /*<<< orphan*/ * dai_name; } ;
struct TYPE_7__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_5__*,struct snd_soc_card*) ; 
 int mxs_saif_get_mclk (int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_card mxs_sgtl5000 ; 
 TYPE_4__* mxs_sgtl5000_dai ; 
 int /*<<< orphan*/  mxs_sgtl5000_dapm_widgets ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 

__attribute__((used)) static int mxs_sgtl5000_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &mxs_sgtl5000;
	int ret, i;
	struct device_node *np = pdev->dev.of_node;
	struct device_node *saif_np[2], *codec_np;

	saif_np[0] = of_parse_phandle(np, "saif-controllers", 0);
	saif_np[1] = of_parse_phandle(np, "saif-controllers", 1);
	codec_np = of_parse_phandle(np, "audio-codec", 0);
	if (!saif_np[0] || !saif_np[1] || !codec_np) {
		dev_err(&pdev->dev, "phandle missing or invalid\n");
		return -EINVAL;
	}

	for (i = 0; i < 2; i++) {
		mxs_sgtl5000_dai[i].codecs->name = NULL;
		mxs_sgtl5000_dai[i].codecs->of_node = codec_np;
		mxs_sgtl5000_dai[i].cpus->dai_name = NULL;
		mxs_sgtl5000_dai[i].cpus->of_node = saif_np[i];
		mxs_sgtl5000_dai[i].platforms->name = NULL;
		mxs_sgtl5000_dai[i].platforms->of_node = saif_np[i];
	}

	of_node_put(codec_np);
	of_node_put(saif_np[0]);
	of_node_put(saif_np[1]);

	/*
	 * Set an init clock(11.28Mhz) for sgtl5000 initialization(i2c r/w).
	 * The Sgtl5000 sysclk is derived from saif0 mclk and it's range
	 * should be >= 8MHz and <= 27M.
	 */
	ret = mxs_saif_get_mclk(0, 44100 * 256, 44100);
	if (ret) {
		dev_err(&pdev->dev, "failed to get mclk\n");
		return ret;
	}

	card->dev = &pdev->dev;

	if (of_find_property(np, "audio-routing", NULL)) {
		card->dapm_widgets = mxs_sgtl5000_dapm_widgets;
		card->num_dapm_widgets = ARRAY_SIZE(mxs_sgtl5000_dapm_widgets);

		ret = snd_soc_of_parse_audio_routing(card, "audio-routing");
		if (ret) {
			dev_err(&pdev->dev, "failed to parse audio-routing (%d)\n",
				ret);
			return ret;
		}
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
				ret);
		return ret;
	}

	return 0;
}