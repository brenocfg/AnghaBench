#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_2__* dev; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * codec_of_node; int /*<<< orphan*/ * cpu_of_node; int /*<<< orphan*/ * platform_of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_2__*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
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
		ret = -EINVAL;
		goto put_codec_of_node;
	}

	rk_dailink.platform_of_node = rk_dailink.cpu_of_node;

	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	if (ret) {
		dev_err(&pdev->dev,
			"Soc parse card name failed %d\n", ret);
		goto put_cpu_of_node;
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret) {
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		goto put_cpu_of_node;
	}

	return ret;

put_cpu_of_node:
	of_node_put(rk_dailink.cpu_of_node);
	rk_dailink.cpu_of_node = NULL;
put_codec_of_node:
	of_node_put(rk_dailink.codec_of_node);
	rk_dailink.codec_of_node = NULL;

	return ret;
}