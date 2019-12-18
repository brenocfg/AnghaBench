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
struct cs42l73_private {int shutdwn_delay; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct cs42l73_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l73_ear_amp_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs42l73_private *priv = snd_soc_component_get_drvdata(component);
	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		/* 50 ms delay between setting PDN and MCLKDIS */
		if (priv->shutdwn_delay < 50)
			priv->shutdwn_delay = 50;
		break;
	default:
		pr_err("Invalid event = 0x%x\n", event);
	}
	return 0;
}