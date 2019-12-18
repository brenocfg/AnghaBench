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
struct snd_soc_card {TYPE_5__* dev; } ;
struct rk_drvdata {int gpio_hp_det; int gpio_hp_en; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct of_phandle_args {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {TYPE_3__* cpus; TYPE_2__* platforms; TYPE_1__* codecs; } ;
struct TYPE_11__ {void* of_node; } ;
struct TYPE_10__ {void* of_node; } ;
struct TYPE_9__ {int /*<<< orphan*/  dai_name; void* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int devm_gpio_request_one (TYPE_5__*,int,int /*<<< orphan*/ ,char*) ; 
 struct rk_drvdata* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_5__*,struct snd_soc_card*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_fixed_args (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 TYPE_4__ rk_dailink ; 
 struct snd_soc_card snd_soc_card_rk ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct rk_drvdata*) ; 
 int snd_soc_get_dai_name (struct of_phandle_args*,int /*<<< orphan*/ *) ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 

__attribute__((used)) static int snd_rk_mc_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &snd_soc_card_rk;
	struct device_node *np = pdev->dev.of_node;
	struct rk_drvdata *machine;
	struct of_phandle_args args;

	machine = devm_kzalloc(&pdev->dev, sizeof(struct rk_drvdata),
			       GFP_KERNEL);
	if (!machine)
		return -ENOMEM;

	card->dev = &pdev->dev;

	machine->gpio_hp_det = of_get_named_gpio(np,
		"rockchip,hp-det-gpios", 0);
	if (!gpio_is_valid(machine->gpio_hp_det) && machine->gpio_hp_det != -ENODEV)
		return machine->gpio_hp_det;

	machine->gpio_hp_en = of_get_named_gpio(np,
		"rockchip,hp-en-gpios", 0);
	if (!gpio_is_valid(machine->gpio_hp_en) && machine->gpio_hp_en != -ENODEV)
		return machine->gpio_hp_en;

	if (gpio_is_valid(machine->gpio_hp_en)) {
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_hp_en,
					    GPIOF_OUT_INIT_LOW, "hp_en");
		if (ret) {
			dev_err(card->dev, "cannot get hp_en gpio\n");
			return ret;
		}
	}

	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	if (ret) {
		dev_err(card->dev, "SoC parse card name failed %d\n", ret);
		return ret;
	}

	rk_dailink.codecs[0].of_node = of_parse_phandle(np,
							"rockchip,audio-codec",
							0);
	if (!rk_dailink.codecs[0].of_node) {
		dev_err(&pdev->dev,
			"Property 'rockchip,audio-codec' missing or invalid\n");
		return -EINVAL;
	}
	ret = of_parse_phandle_with_fixed_args(np, "rockchip,audio-codec",
					       0, 0, &args);
	if (ret) {
		dev_err(&pdev->dev,
			"Unable to parse property 'rockchip,audio-codec'\n");
		return ret;
	}

	ret = snd_soc_get_dai_name(&args, &rk_dailink.codecs[0].dai_name);
	if (ret) {
		dev_err(&pdev->dev, "Unable to get codec_dai_name\n");
		return ret;
	}

	rk_dailink.cpus->of_node = of_parse_phandle(np, "rockchip,i2s-controller",
						  0);
	if (!rk_dailink.cpus->of_node) {
		dev_err(&pdev->dev,
			"Property 'rockchip,i2s-controller' missing or invalid\n");
		return -EINVAL;
	}

	rk_dailink.platforms->of_node = rk_dailink.cpus->of_node;

	ret = snd_soc_of_parse_audio_routing(card, "rockchip,routing");
	if (ret) {
		dev_err(&pdev->dev,
			"Unable to parse 'rockchip,routing' property\n");
		return ret;
	}

	snd_soc_card_set_drvdata(card, machine);

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (ret) {
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		return ret;
	}

	return ret;
}