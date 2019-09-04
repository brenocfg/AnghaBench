#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 struct snd_soc_card audiosense_pi_card ; 
 struct snd_soc_dai_link* audiosense_pi_card_dai ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int audiosense_pi_card_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &audiosense_pi_card;
	struct snd_soc_dai_link *dai = &audiosense_pi_card_dai[0];
	struct device_node *i2s_node = pdev->dev.of_node;

	card->dev = &pdev->dev;

	if (!dai) {
		dev_err(&pdev->dev, "DAI not found. Missing or Invalid\n");
		return -EINVAL;
	}

	i2s_node = of_parse_phandle(pdev->dev.of_node, "i2s-controller", 0);
	if (!i2s_node) {
		dev_err(&pdev->dev,
			"Property 'i2s-controller' missing or invalid\n");
		return -EINVAL;
	}

	dai->cpu_dai_name = NULL;
	dai->cpu_of_node = i2s_node;
	dai->platform_name = NULL;
	dai->platform_of_node = i2s_node;

	of_node_put(i2s_node);

	ret = snd_soc_register_card(card);
	if (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);

	return ret;
}