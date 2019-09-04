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
struct tegra_alc5632 {int /*<<< orphan*/  gpio_hp_det; } ;
struct snd_soc_pcm_runtime {TYPE_3__* card; } ;
struct TYPE_6__ {int /*<<< orphan*/  dapm; } ;
struct TYPE_5__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct tegra_alc5632* snd_soc_card_get_drvdata (TYPE_3__*) ; 
 int snd_soc_card_jack_new (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 TYPE_1__ tegra_alc5632_hp_jack_gpio ; 
 int /*<<< orphan*/  tegra_alc5632_hs_jack ; 
 int /*<<< orphan*/  tegra_alc5632_hs_jack_pins ; 

__attribute__((used)) static int tegra_alc5632_asoc_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	struct tegra_alc5632 *machine = snd_soc_card_get_drvdata(rtd->card);

	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET,
				    &tegra_alc5632_hs_jack,
				    tegra_alc5632_hs_jack_pins,
				    ARRAY_SIZE(tegra_alc5632_hs_jack_pins));
	if (ret)
		return ret;

	if (gpio_is_valid(machine->gpio_hp_det)) {
		tegra_alc5632_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_alc5632_hs_jack,
						1,
						&tegra_alc5632_hp_jack_gpio);
	}

	snd_soc_dapm_force_enable_pin(&rtd->card->dapm, "MICBIAS1");

	return 0;
}