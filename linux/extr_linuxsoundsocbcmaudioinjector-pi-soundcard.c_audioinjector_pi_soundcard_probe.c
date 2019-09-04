#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* cpu_of_node; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; int /*<<< orphan*/ * cpu_dai_name; } ;
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_soc_dai_link* audioinjector_pi_soundcard_dai ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_1__*,struct snd_soc_card*) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_card snd_soc_audioinjector ; 

__attribute__((used)) static int audioinjector_pi_soundcard_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_audioinjector;
	int ret;
	
	card->dev = &pdev->dev;

	if (pdev->dev.of_node) {
		struct snd_soc_dai_link *dai = &audioinjector_pi_soundcard_dai[0];
		struct device_node *i2s_node = of_parse_phandle(pdev->dev.of_node,
								"i2s-controller", 0);

		if (i2s_node) {
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = i2s_node;
			dai->platform_name = NULL;
			dai->platform_of_node = i2s_node;
		} else
			if (!dai->cpu_of_node) {
				dev_err(&pdev->dev, "Property 'i2s-controller' missing or invalid\n");
				return -EINVAL;
			}
	}

	if ((ret = devm_snd_soc_register_card(&pdev->dev, card))) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
	}
	return ret;
}