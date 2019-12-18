#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tpa6130a2_data {int dummy; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 struct tpa6130a2_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int tpa6130a2_power (struct tpa6130a2_data*,int) ; 

__attribute__((used)) static int tpa6130a2_power_event(struct snd_soc_dapm_widget *w,
				 struct snd_kcontrol *kctrl, int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct tpa6130a2_data *data = snd_soc_component_get_drvdata(c);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		/* Before widget power up: turn chip on, sync registers */
		return tpa6130a2_power(data, true);
	} else {
		/* After widget power down: turn chip off */
		return tpa6130a2_power(data, false);
	}
}