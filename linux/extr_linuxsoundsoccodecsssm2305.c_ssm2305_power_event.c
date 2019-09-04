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
struct ssm2305 {int /*<<< orphan*/  gpiod_shutdown; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ssm2305* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssm2305_power_event(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kctrl, int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct ssm2305 *data = snd_soc_component_get_drvdata(c);

	gpiod_set_value_cansleep(data->gpiod_shutdown,
				 SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}