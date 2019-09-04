#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {void* codec_of_node; int /*<<< orphan*/ * codec_name; void* cpu_of_node; void* platform_of_node; int /*<<< orphan*/  platform_name; int /*<<< orphan*/  cpu_dai_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 struct snd_soc_card arndale_rt5631 ; 
 TYPE_3__* arndale_rt5631_dai ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_1__*,struct snd_soc_card*) ; 
 void* of_parse_phandle (struct device_node*,char*,int) ; 

__attribute__((used)) static int arndale_audio_probe(struct platform_device *pdev)
{
	int n, ret;
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &arndale_rt5631;

	card->dev = &pdev->dev;

	for (n = 0; np && n < ARRAY_SIZE(arndale_rt5631_dai); n++) {
		if (!arndale_rt5631_dai[n].cpu_dai_name) {
			arndale_rt5631_dai[n].cpu_of_node = of_parse_phandle(np,
					"samsung,audio-cpu", n);

			if (!arndale_rt5631_dai[n].cpu_of_node) {
				dev_err(&pdev->dev,
				"Property 'samsung,audio-cpu' missing or invalid\n");
				return -EINVAL;
			}
		}
		if (!arndale_rt5631_dai[n].platform_name)
			arndale_rt5631_dai[n].platform_of_node =
					arndale_rt5631_dai[n].cpu_of_node;

		arndale_rt5631_dai[n].codec_name = NULL;
		arndale_rt5631_dai[n].codec_of_node = of_parse_phandle(np,
					"samsung,audio-codec", n);
		if (!arndale_rt5631_dai[0].codec_of_node) {
			dev_err(&pdev->dev,
			"Property 'samsung,audio-codec' missing or invalid\n");
			return -EINVAL;
		}
	}

	ret = devm_snd_soc_register_card(card->dev, card);

	if (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed:%d\n", ret);

	return ret;
}