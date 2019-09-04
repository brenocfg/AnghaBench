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
struct snd_soc_dai_link {char* name; char* stream_name; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; } ;
struct snd_soc_card {char* name; int /*<<< orphan*/  set_bias_level; TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int digital_gain_0db_limit ; 
 scalar_t__ mute_gpio ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_bool (scalar_t__,char*) ; 
 scalar_t__ of_property_read_string (scalar_t__,char*,char**) ; 
 struct snd_soc_card snd_rpi_iqaudio_dac ; 
 struct snd_soc_dai_link* snd_rpi_iqaudio_dac_dai ; 
 int /*<<< orphan*/  snd_rpi_iqaudio_gpio_unmute (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_rpi_iqaudio_set_bias_level ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int snd_rpi_iqaudio_dac_probe(struct platform_device *pdev)
{
	int ret = 0;
	bool gpio_unmute = false;

	snd_rpi_iqaudio_dac.dev = &pdev->dev;

	if (pdev->dev.of_node) {
		struct device_node *i2s_node;
		struct snd_soc_card *card = &snd_rpi_iqaudio_dac;
		struct snd_soc_dai_link *dai = &snd_rpi_iqaudio_dac_dai[0];
		bool auto_gpio_mute = false;

		i2s_node = of_parse_phandle(pdev->dev.of_node,
					    "i2s-controller", 0);
		if (i2s_node) {
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = i2s_node;
			dai->platform_name = NULL;
			dai->platform_of_node = i2s_node;
		}

		digital_gain_0db_limit = !of_property_read_bool(
			pdev->dev.of_node, "iqaudio,24db_digital_gain");

		if (of_property_read_string(pdev->dev.of_node, "card_name",
					    &card->name))
			card->name = "IQaudIODAC";

		if (of_property_read_string(pdev->dev.of_node, "dai_name",
					    &dai->name))
			dai->name = "IQaudIO DAC";

		if (of_property_read_string(pdev->dev.of_node,
					"dai_stream_name", &dai->stream_name))
			dai->stream_name = "IQaudIO DAC HiFi";

		/* gpio_unmute - one time unmute amp using GPIO */
		gpio_unmute = of_property_read_bool(pdev->dev.of_node,
						    "iqaudio-dac,unmute-amp");

		/* auto_gpio_mute - mute/unmute amp using GPIO */
		auto_gpio_mute = of_property_read_bool(pdev->dev.of_node,
						"iqaudio-dac,auto-mute-amp");

		if (auto_gpio_mute || gpio_unmute) {
			mute_gpio = devm_gpiod_get_optional(&pdev->dev, "mute",
							    GPIOD_OUT_LOW);
			if (IS_ERR(mute_gpio)) {
				ret = PTR_ERR(mute_gpio);
				dev_err(&pdev->dev,
					"Failed to get mute gpio: %d\n", ret);
				return ret;
			}

			if (auto_gpio_mute && mute_gpio)
				snd_rpi_iqaudio_dac.set_bias_level =
						snd_rpi_iqaudio_set_bias_level;
		}
	}

	ret = snd_soc_register_card(&snd_rpi_iqaudio_dac);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"snd_soc_register_card() failed: %d\n", ret);
		return ret;
	}

	if (gpio_unmute && mute_gpio)
		snd_rpi_iqaudio_gpio_unmute(&snd_rpi_iqaudio_dac);

	return 0;
}