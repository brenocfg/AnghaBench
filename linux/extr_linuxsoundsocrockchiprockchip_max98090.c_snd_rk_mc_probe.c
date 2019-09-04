#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_3__* dev; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {void* codec_of_node; } ;
struct TYPE_5__ {void* cpu_of_node; void* platform_of_node; void* codec_of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_3__*,struct snd_soc_card*) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ rk_98090_headset_dev ; 
 TYPE_1__ rk_dailink ; 
 struct snd_soc_card snd_soc_card_rk ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 

__attribute__((used)) static int snd_rk_mc_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &snd_soc_card_rk;
	struct device_node *np = pdev->dev.of_node;

	/* register the soc card */
	card->dev = &pdev->dev;

	rk_dailink.codec_of_node = of_parse_phandle(np,
			"rockchip,audio-codec", 0);
	if (!rk_dailink.codec_of_node) {
		dev_err(&pdev->dev,
			"Property 'rockchip,audio-codec' missing or invalid\n");
		return -EINVAL;
	}

	rk_dailink.cpu_of_node = of_parse_phandle(np,
			"rockchip,i2s-controller", 0);
	if (!rk_dailink.cpu_of_node) {
		dev_err(&pdev->dev,
			"Property 'rockchip,i2s-controller' missing or invalid\n");
		return -EINVAL;
	}

	rk_dailink.platform_of_node = rk_dailink.cpu_of_node;

	rk_98090_headset_dev.codec_of_node = of_parse_phandle(np,
			"rockchip,headset-codec", 0);
	if (!rk_98090_headset_dev.codec_of_node) {
		dev_err(&pdev->dev,
			"Property 'rockchip,headset-codec' missing/invalid\n");
		return -EINVAL;
	}

	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	if (ret) {
		dev_err(&pdev->dev,
			"Soc parse card name failed %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret) {
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		return ret;
	}

	return ret;
}