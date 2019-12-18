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
struct tegra_rt5640 {int gpio_hp_det_flags; int /*<<< orphan*/  gpio_hp_det; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct TYPE_3__ {int invert; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tegra_rt5640* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_rt5640_hp_jack ; 
 TYPE_1__ tegra_rt5640_hp_jack_gpio ; 
 int /*<<< orphan*/  tegra_rt5640_hp_jack_pins ; 

__attribute__((used)) static int tegra_rt5640_asoc_init(struct snd_soc_pcm_runtime *rtd)
{
	struct tegra_rt5640 *machine = snd_soc_card_get_drvdata(rtd->card);

	snd_soc_card_jack_new(rtd->card, "Headphones", SND_JACK_HEADPHONE,
			      &tegra_rt5640_hp_jack, tegra_rt5640_hp_jack_pins,
			      ARRAY_SIZE(tegra_rt5640_hp_jack_pins));

	if (gpio_is_valid(machine->gpio_hp_det)) {
		tegra_rt5640_hp_jack_gpio.gpio = machine->gpio_hp_det;
		tegra_rt5640_hp_jack_gpio.invert =
			!!(machine->gpio_hp_det_flags & OF_GPIO_ACTIVE_LOW);
		snd_soc_jack_add_gpios(&tegra_rt5640_hp_jack,
						1,
						&tegra_rt5640_hp_jack_gpio);
	}

	return 0;
}