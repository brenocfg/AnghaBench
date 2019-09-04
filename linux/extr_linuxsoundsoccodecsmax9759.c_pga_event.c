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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct max9759 {int /*<<< orphan*/  gpiod_shutdown; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct max9759* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pga_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *control, int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct max9759 *priv = snd_soc_component_get_drvdata(c);

	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_value_cansleep(priv->gpiod_shutdown, 0);
	else
		gpiod_set_value_cansleep(priv->gpiod_shutdown, 1);

	return 0;
}