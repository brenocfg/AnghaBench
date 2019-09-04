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
struct simple_amp {int /*<<< orphan*/  gpiod_enable; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct simple_amp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drv_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *control, int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct simple_amp *priv = snd_soc_component_get_drvdata(c);
	int val;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		val = 1;
		break;
	case SND_SOC_DAPM_PRE_PMD:
		val = 0;
		break;
	default:
		WARN(1, "Unexpected event");
		return -EINVAL;
	}

	gpiod_set_value_cansleep(priv->gpiod_enable, val);

	return 0;
}