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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {int dummy; } ;
struct pcm3008_setup_data {int /*<<< orphan*/  pdda_pin; } ;
struct TYPE_2__ {struct pcm3008_setup_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm3008_dac_ev(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol,
			  int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct pcm3008_setup_data *setup = component->dev->platform_data;

	gpio_set_value_cansleep(setup->pdda_pin,
				SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}