#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tegra_alc5632 {int gpio_hp_det; int /*<<< orphan*/  util_data; } ;
struct snd_soc_card {TYPE_4__* dev; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_10__ {int /*<<< orphan*/ * of_node; } ;
struct TYPE_9__ {int /*<<< orphan*/ * of_node; } ;
struct TYPE_8__ {int /*<<< orphan*/ * of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct tegra_alc5632* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tegra_alc5632*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 struct snd_soc_card snd_soc_tegra_alc5632 ; 
 TYPE_5__ tegra_alc5632_dai ; 
 int /*<<< orphan*/  tegra_asoc_utils_fini (int /*<<< orphan*/ *) ; 
 int tegra_asoc_utils_init (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int tegra_alc5632_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &snd_soc_tegra_alc5632;
	struct tegra_alc5632 *alc5632;
	int ret;

	alc5632 = devm_kzalloc(&pdev->dev,
			sizeof(struct tegra_alc5632), GFP_KERNEL);
	if (!alc5632)
		return -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, alc5632);

	alc5632->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	if (alc5632->gpio_hp_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	if (ret)
		goto err;

	tegra_alc5632_dai.codecs->of_node = of_parse_phandle(
			pdev->dev.of_node, "nvidia,audio-codec", 0);

	if (!tegra_alc5632_dai.codecs->of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_alc5632_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	if (!tegra_alc5632_dai.cpus->of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		goto err_put_codec_of_node;
	}

	tegra_alc5632_dai.platforms->of_node = tegra_alc5632_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&alc5632->util_data, &pdev->dev);
	if (ret)
		goto err_put_cpu_of_node;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		goto err_fini_utils;
	}

	return 0;

err_fini_utils:
	tegra_asoc_utils_fini(&alc5632->util_data);
err_put_cpu_of_node:
	of_node_put(tegra_alc5632_dai.cpus->of_node);
	tegra_alc5632_dai.cpus->of_node = NULL;
	tegra_alc5632_dai.platforms->of_node = NULL;
err_put_codec_of_node:
	of_node_put(tegra_alc5632_dai.codecs->of_node);
	tegra_alc5632_dai.codecs->of_node = NULL;
err:
	return ret;
}