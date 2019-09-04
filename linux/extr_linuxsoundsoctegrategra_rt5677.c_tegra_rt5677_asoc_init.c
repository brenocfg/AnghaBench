#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tegra_rt5677 {int /*<<< orphan*/  gpio_mic_present; int /*<<< orphan*/  gpio_hp_det; } ;
struct snd_soc_pcm_runtime {TYPE_4__* card; } ;
struct TYPE_7__ {int /*<<< orphan*/  dapm; } ;
struct TYPE_6__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  SND_JACK_MICROPHONE ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tegra_rt5677* snd_soc_card_get_drvdata (TYPE_4__*) ; 
 int /*<<< orphan*/  snd_soc_card_jack_new (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_rt5677_hp_jack ; 
 TYPE_1__ tegra_rt5677_hp_jack_gpio ; 
 int /*<<< orphan*/  tegra_rt5677_hp_jack_pins ; 
 int /*<<< orphan*/  tegra_rt5677_mic_jack ; 
 TYPE_1__ tegra_rt5677_mic_jack_gpio ; 
 int /*<<< orphan*/  tegra_rt5677_mic_jack_pins ; 

__attribute__((used)) static int tegra_rt5677_asoc_init(struct snd_soc_pcm_runtime *rtd)
{
	struct tegra_rt5677 *machine = snd_soc_card_get_drvdata(rtd->card);

	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE,
			      &tegra_rt5677_hp_jack,
			      &tegra_rt5677_hp_jack_pins, 1);

	if (gpio_is_valid(machine->gpio_hp_det)) {
		tegra_rt5677_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_rt5677_hp_jack, 1,
				&tegra_rt5677_hp_jack_gpio);
	}


	snd_soc_card_jack_new(rtd->card, "Mic Jack", SND_JACK_MICROPHONE,
			      &tegra_rt5677_mic_jack,
			      &tegra_rt5677_mic_jack_pins, 1);

	if (gpio_is_valid(machine->gpio_mic_present)) {
		tegra_rt5677_mic_jack_gpio.gpio = machine->gpio_mic_present;
		snd_soc_jack_add_gpios(&tegra_rt5677_mic_jack, 1,
				&tegra_rt5677_mic_jack_gpio);
	}

	snd_soc_dapm_force_enable_pin(&rtd->card->dapm, "MICBIAS1");

	return 0;
}