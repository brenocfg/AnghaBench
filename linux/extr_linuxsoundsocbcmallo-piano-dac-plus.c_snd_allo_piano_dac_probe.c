#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct snd_soc_card {int num_links; int /*<<< orphan*/  set_bias_level; TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {void* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 TYPE_3__* allo_piano_2_1_codecs ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int digital_gain_0db_limit ; 
 scalar_t__ glb_mclk ; 
 scalar_t__* mute_gpio ; 
 void* of_parse_phandle (scalar_t__,char*,int) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct snd_soc_card*) ; 
 struct snd_soc_card snd_allo_piano_dac ; 
 struct snd_soc_dai_link* snd_allo_piano_dac_dai ; 
 int /*<<< orphan*/  snd_allo_piano_gpio_mute (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_allo_piano_set_bias_level ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int snd_allo_piano_dac_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_allo_piano_dac;
	int ret = 0, i = 0;

	card->dev = &pdev->dev;
	platform_set_drvdata(pdev, &snd_allo_piano_dac);

	if (pdev->dev.of_node) {
		struct device_node *i2s_node;
		struct snd_soc_dai_link *dai;

		dai = &snd_allo_piano_dac_dai[0];
		i2s_node = of_parse_phandle(pdev->dev.of_node,
						"i2s-controller", 0);
		if (i2s_node) {
			for (i = 0; i < card->num_links; i++) {
				dai->cpu_dai_name = NULL;
				dai->cpu_of_node = i2s_node;
				dai->platform_name = NULL;
				dai->platform_of_node = i2s_node;
			}
		}
		digital_gain_0db_limit =
			!of_property_read_bool(pdev->dev.of_node,
						"allo,24db_digital_gain");

		glb_mclk = of_property_read_bool(pdev->dev.of_node,
						"allo,glb_mclk");

		allo_piano_2_1_codecs[0].of_node =
			of_parse_phandle(pdev->dev.of_node, "audio-codec", 0);
		if (!allo_piano_2_1_codecs[0].of_node) {
			dev_err(&pdev->dev,
				"Property 'audio-codec' missing or invalid\n");
			return -EINVAL;
		}

		allo_piano_2_1_codecs[1].of_node =
			of_parse_phandle(pdev->dev.of_node, "audio-codec", 1);
		if (!allo_piano_2_1_codecs[1].of_node) {
			dev_err(&pdev->dev,
				"Property 'audio-codec' missing or invalid\n");
			return -EINVAL;
		}

		mute_gpio[0] = devm_gpiod_get_optional(&pdev->dev, "mute1",
							GPIOD_OUT_LOW);
		if (IS_ERR(mute_gpio[0])) {
			ret = PTR_ERR(mute_gpio[0]);
			dev_err(&pdev->dev,
				"failed to get mute1 gpio6: %d\n", ret);
			return ret;
		}

		mute_gpio[1] = devm_gpiod_get_optional(&pdev->dev, "mute2",
							GPIOD_OUT_LOW);
		if (IS_ERR(mute_gpio[1])) {
			ret = PTR_ERR(mute_gpio[1]);
			dev_err(&pdev->dev,
				"failed to get mute2 gpio25: %d\n", ret);
			return ret;
		}

		if (mute_gpio[0] && mute_gpio[1])
			snd_allo_piano_dac.set_bias_level =
				snd_allo_piano_set_bias_level;

		ret = snd_soc_register_card(&snd_allo_piano_dac);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"snd_soc_register_card() failed: %d\n", ret);
			return ret;
		}

		if ((mute_gpio[0]) && (mute_gpio[1]))
			snd_allo_piano_gpio_mute(&snd_allo_piano_dac);

		return 0;
	}

	return -EINVAL;
}