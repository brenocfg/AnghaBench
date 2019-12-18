#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tegra_rt5677 {int gpio_hp_det; int gpio_mic_present; int gpio_hp_en; int gpio_dmic_clk_en; int /*<<< orphan*/  util_data; } ;
struct snd_soc_card {TYPE_5__* dev; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_11__ {int /*<<< orphan*/ * of_node; } ;
struct TYPE_10__ {int /*<<< orphan*/ * of_node; } ;
struct TYPE_9__ {int /*<<< orphan*/ * of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int devm_gpio_request_one (TYPE_5__*,int,int /*<<< orphan*/ ,char*) ; 
 struct tegra_rt5677* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tegra_rt5677*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 struct snd_soc_card snd_soc_tegra_rt5677 ; 
 int /*<<< orphan*/  tegra_asoc_utils_fini (int /*<<< orphan*/ *) ; 
 int tegra_asoc_utils_init (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_4__ tegra_rt5677_dai ; 

__attribute__((used)) static int tegra_rt5677_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &snd_soc_tegra_rt5677;
	struct tegra_rt5677 *machine;
	int ret;

	machine = devm_kzalloc(&pdev->dev,
			sizeof(struct tegra_rt5677), GFP_KERNEL);
	if (!machine)
		return -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	if (machine->gpio_hp_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	machine->gpio_mic_present = of_get_named_gpio(np,
			"nvidia,mic-present-gpios", 0);
	if (machine->gpio_mic_present == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	machine->gpio_hp_en = of_get_named_gpio(np, "nvidia,hp-en-gpios", 0);
	if (machine->gpio_hp_en == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (gpio_is_valid(machine->gpio_hp_en)) {
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_hp_en,
				GPIOF_OUT_INIT_LOW, "hp_en");
		if (ret) {
			dev_err(card->dev, "cannot get hp_en gpio\n");
			return ret;
		}
	}

	machine->gpio_dmic_clk_en = of_get_named_gpio(np,
		"nvidia,dmic-clk-en-gpios", 0);
	if (machine->gpio_dmic_clk_en == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (gpio_is_valid(machine->gpio_dmic_clk_en)) {
		ret = devm_gpio_request_one(&pdev->dev,
				machine->gpio_dmic_clk_en,
				GPIOF_OUT_INIT_HIGH, "dmic_clk_en");
		if (ret) {
			dev_err(card->dev, "cannot get dmic_clk_en gpio\n");
			return ret;
		}
	}

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	if (ret)
		goto err;

	tegra_rt5677_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	if (!tegra_rt5677_dai.codecs->of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_rt5677_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	if (!tegra_rt5677_dai.cpus->of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		goto err_put_codec_of_node;
	}
	tegra_rt5677_dai.platforms->of_node = tegra_rt5677_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
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
	tegra_asoc_utils_fini(&machine->util_data);
err_put_cpu_of_node:
	of_node_put(tegra_rt5677_dai.cpus->of_node);
	tegra_rt5677_dai.cpus->of_node = NULL;
	tegra_rt5677_dai.platforms->of_node = NULL;
err_put_codec_of_node:
	of_node_put(tegra_rt5677_dai.codecs->of_node);
	tegra_rt5677_dai.codecs->of_node = NULL;
err:
	return ret;
}