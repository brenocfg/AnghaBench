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
struct snd_soc_pcm_runtime {TYPE_1__* card; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct TYPE_2__ {struct snd_soc_dapm_context dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  smartq_jack ; 
 int /*<<< orphan*/  smartq_jack_gpios ; 
 int /*<<< orphan*/  smartq_jack_pins ; 
 int snd_soc_card_jack_new (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_dapm_context*,char*) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smartq_wm8987_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dapm_context *dapm = &rtd->card->dapm;
	int err = 0;

	/* set endpoints to not connected */
	snd_soc_dapm_nc_pin(dapm, "LINPUT1");
	snd_soc_dapm_nc_pin(dapm, "RINPUT1");
	snd_soc_dapm_nc_pin(dapm, "OUT3");
	snd_soc_dapm_nc_pin(dapm, "ROUT1");

	/* Headphone jack detection */
	err = snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				    SND_JACK_HEADPHONE, &smartq_jack,
				    smartq_jack_pins,
				    ARRAY_SIZE(smartq_jack_pins));
	if (err)
		return err;

	err = snd_soc_jack_add_gpios(&smartq_jack,
				     ARRAY_SIZE(smartq_jack_gpios),
				     smartq_jack_gpios);

	return err;
}