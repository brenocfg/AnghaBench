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
struct tegra_wm8753 {int /*<<< orphan*/  util_data; } ;
struct snd_soc_card {TYPE_2__* dev; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {void* cpu_of_node; void* platform_of_node; void* codec_of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct tegra_wm8753* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tegra_wm8753*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 struct snd_soc_card snd_soc_tegra_wm8753 ; 
 int /*<<< orphan*/  tegra_asoc_utils_fini (int /*<<< orphan*/ *) ; 
 int tegra_asoc_utils_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__ tegra_wm8753_dai ; 

__attribute__((used)) static int tegra_wm8753_driver_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &snd_soc_tegra_wm8753;
	struct tegra_wm8753 *machine;
	int ret;

	machine = devm_kzalloc(&pdev->dev, sizeof(struct tegra_wm8753),
			       GFP_KERNEL);
	if (!machine)
		return -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	if (ret)
		goto err;

	tegra_wm8753_dai.codec_of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	if (!tegra_wm8753_dai.codec_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_wm8753_dai.cpu_of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	if (!tegra_wm8753_dai.cpu_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_wm8753_dai.platform_of_node = tegra_wm8753_dai.cpu_of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	if (ret)
		goto err;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		goto err_fini_utils;
	}

	return 0;

err_fini_utils:
	tegra_asoc_utils_fini(&machine->util_data);
err:
	return ret;
}