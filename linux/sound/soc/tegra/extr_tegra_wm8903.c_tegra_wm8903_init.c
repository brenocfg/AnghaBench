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
struct tegra_wm8903 {int /*<<< orphan*/  gpio_hp_det; } ;
struct snd_soc_pcm_runtime {struct snd_soc_card* card; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  SND_JACK_MICROPHONE ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tegra_wm8903* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_card_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_wm8903_hp_jack ; 
 TYPE_1__ tegra_wm8903_hp_jack_gpio ; 
 int /*<<< orphan*/  tegra_wm8903_hp_jack_pins ; 
 int /*<<< orphan*/  tegra_wm8903_mic_jack ; 
 int /*<<< orphan*/  tegra_wm8903_mic_jack_pins ; 
 int /*<<< orphan*/  wm8903_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_wm8903_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = codec_dai->component;
	struct snd_soc_card *card = rtd->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);

	if (gpio_is_valid(machine->gpio_hp_det)) {
		tegra_wm8903_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				      SND_JACK_HEADPHONE, &tegra_wm8903_hp_jack,
				      tegra_wm8903_hp_jack_pins,
				      ARRAY_SIZE(tegra_wm8903_hp_jack_pins));
		snd_soc_jack_add_gpios(&tegra_wm8903_hp_jack,
					1,
					&tegra_wm8903_hp_jack_gpio);
	}

	snd_soc_card_jack_new(rtd->card, "Mic Jack", SND_JACK_MICROPHONE,
			      &tegra_wm8903_mic_jack,
			      tegra_wm8903_mic_jack_pins,
			      ARRAY_SIZE(tegra_wm8903_mic_jack_pins));
	wm8903_mic_detect(component, &tegra_wm8903_mic_jack, SND_JACK_MICROPHONE,
				0);

	snd_soc_dapm_force_enable_pin(&card->dapm, "MICBIAS");

	return 0;
}