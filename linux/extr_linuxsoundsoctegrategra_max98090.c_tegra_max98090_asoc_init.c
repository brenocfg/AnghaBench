#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_max98090 {int /*<<< orphan*/  gpio_mic_det; int /*<<< orphan*/  gpio_hp_det; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  SND_JACK_MICROPHONE ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tegra_max98090* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_max98090_hp_jack ; 
 TYPE_1__ tegra_max98090_hp_jack_gpio ; 
 int /*<<< orphan*/  tegra_max98090_hp_jack_pins ; 
 int /*<<< orphan*/  tegra_max98090_mic_jack ; 
 TYPE_1__ tegra_max98090_mic_jack_gpio ; 
 int /*<<< orphan*/  tegra_max98090_mic_jack_pins ; 

__attribute__((used)) static int tegra_max98090_asoc_init(struct snd_soc_pcm_runtime *rtd)
{
	struct tegra_max98090 *machine = snd_soc_card_get_drvdata(rtd->card);

	if (gpio_is_valid(machine->gpio_hp_det)) {
		snd_soc_card_jack_new(rtd->card, "Headphones",
				      SND_JACK_HEADPHONE,
				      &tegra_max98090_hp_jack,
				      tegra_max98090_hp_jack_pins,
				      ARRAY_SIZE(tegra_max98090_hp_jack_pins));

		tegra_max98090_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_max98090_hp_jack,
					1,
					&tegra_max98090_hp_jack_gpio);
	}

	if (gpio_is_valid(machine->gpio_mic_det)) {
		snd_soc_card_jack_new(rtd->card, "Mic Jack",
				      SND_JACK_MICROPHONE,
				      &tegra_max98090_mic_jack,
				      tegra_max98090_mic_jack_pins,
				      ARRAY_SIZE(tegra_max98090_mic_jack_pins));

		tegra_max98090_mic_jack_gpio.gpio = machine->gpio_mic_det;
		snd_soc_jack_add_gpios(&tegra_max98090_mic_jack,
				       1,
				       &tegra_max98090_mic_jack_gpio);
	}

	return 0;
}