#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* codec_of_node; int /*<<< orphan*/ * codec_name; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 struct snd_soc_dai_link* audioinjector_octo_dai ; 
 scalar_t__ codec_rst_gpio ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ devm_gpiod_get_array_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_1__*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mult_gpios ; 
 int /*<<< orphan*/  non_stop_clocks ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (scalar_t__,char*) ; 
 struct snd_soc_card snd_soc_audioinjector_octo ; 

__attribute__((used)) static int audioinjector_octo_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_audioinjector_octo;
	int ret;

	card->dev = &pdev->dev;

	if (pdev->dev.of_node) {
		struct snd_soc_dai_link *dai = &audioinjector_octo_dai[0];
		struct device_node *i2s_node =
					of_parse_phandle(pdev->dev.of_node,
							"i2s-controller", 0);
		struct device_node *codec_node =
					of_parse_phandle(pdev->dev.of_node,
								"codec", 0);

		mult_gpios = devm_gpiod_get_array_optional(&pdev->dev, "mult",
								GPIOD_OUT_LOW);
		if (IS_ERR(mult_gpios))
			return PTR_ERR(mult_gpios);

		codec_rst_gpio = devm_gpiod_get_optional(&pdev->dev, "reset",
								GPIOD_OUT_LOW);
		if (IS_ERR(codec_rst_gpio))
			return PTR_ERR(codec_rst_gpio);

		non_stop_clocks = of_property_read_bool(pdev->dev.of_node, "non-stop-clocks");

		if (codec_rst_gpio)
			gpiod_set_value(codec_rst_gpio, 1);
		msleep(500);
		if (codec_rst_gpio)
			gpiod_set_value(codec_rst_gpio, 0);
		msleep(500);
		if (codec_rst_gpio)
			gpiod_set_value(codec_rst_gpio, 1);
		msleep(500);

		if (i2s_node && codec_node) {
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = i2s_node;
			dai->platform_name = NULL;
			dai->platform_of_node = i2s_node;
			dai->codec_name = NULL;
			dai->codec_of_node = codec_node;
		} else
			if (!i2s_node) {
				dev_err(&pdev->dev,
				"i2s-controller missing or invalid in DT\n");
				return -EINVAL;
			} else {
				dev_err(&pdev->dev,
				"Property 'codec' missing or invalid\n");
				return -EINVAL;
			}
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret != 0)
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
	return ret;
}