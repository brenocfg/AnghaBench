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
struct tegra_max98090 {int gpio_hp_det; int gpio_mic_det; int /*<<< orphan*/  util_data; } ;
struct snd_soc_card {TYPE_2__* dev; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {void* cpu_of_node; void* platform_of_node; void* codec_of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct tegra_max98090* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct tegra_max98090*) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 struct snd_soc_card snd_soc_tegra_max98090 ; 
 int /*<<< orphan*/  tegra_asoc_utils_fini (int /*<<< orphan*/ *) ; 
 int tegra_asoc_utils_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__ tegra_max98090_dai ; 

__attribute__((used)) static int tegra_max98090_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &snd_soc_tegra_max98090;
	struct tegra_max98090 *machine;
	int ret;

	machine = devm_kzalloc(&pdev->dev,
			sizeof(struct tegra_max98090), GFP_KERNEL);
	if (!machine)
		return -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	if (machine->gpio_hp_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	machine->gpio_mic_det =
			of_get_named_gpio(np, "nvidia,mic-det-gpios", 0);
	if (machine->gpio_mic_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	if (ret)
		goto err;

	tegra_max98090_dai.codec_of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	if (!tegra_max98090_dai.codec_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_max98090_dai.cpu_of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	if (!tegra_max98090_dai.cpu_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_max98090_dai.platform_of_node = tegra_max98090_dai.cpu_of_node;

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