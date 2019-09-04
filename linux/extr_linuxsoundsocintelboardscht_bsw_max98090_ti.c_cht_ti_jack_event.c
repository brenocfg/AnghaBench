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
struct snd_soc_jack {TYPE_1__* card; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {struct snd_soc_dapm_context dapm; } ;

/* Variables and functions */
 unsigned long SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int cht_ti_jack_event(struct notifier_block *nb,
		unsigned long event, void *data)
{
	struct snd_soc_jack *jack = (struct snd_soc_jack *)data;
	struct snd_soc_dapm_context *dapm = &jack->card->dapm;

	if (event & SND_JACK_MICROPHONE) {
		snd_soc_dapm_force_enable_pin(dapm, "SHDN");
		snd_soc_dapm_force_enable_pin(dapm, "MICBIAS");
		snd_soc_dapm_sync(dapm);
	} else {
		snd_soc_dapm_disable_pin(dapm, "MICBIAS");
		snd_soc_dapm_disable_pin(dapm, "SHDN");
		snd_soc_dapm_sync(dapm);
	}

	return 0;
}