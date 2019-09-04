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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_GPIO_CONTROL_1 ; 
 int /*<<< orphan*/  PCM512x_GPIO_EN ; 
 int /*<<< orphan*/  PCM512x_GPIO_OUTPUT_4 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ digital_gain_0db_limit ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_limit_volume (struct snd_soc_card*,char*,int) ; 

__attribute__((used)) static int snd_rpi_justboom_dac_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	snd_soc_component_update_bits(component, PCM512x_GPIO_EN, 0x08, 0x08);
	snd_soc_component_update_bits(component, PCM512x_GPIO_OUTPUT_4, 0xf, 0x02);
	snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x08,0x08);

	if (digital_gain_0db_limit)
	{
		int ret;
		struct snd_soc_card *card = rtd->card;

		ret = snd_soc_limit_volume(card, "Digital Playback Volume", 207);
		if (ret < 0)
			dev_warn(card->dev, "Failed to set volume limit: %d\n", ret);
	}

	return 0;
}