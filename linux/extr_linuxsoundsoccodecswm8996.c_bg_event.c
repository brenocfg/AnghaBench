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

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8996_bg_disable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8996_bg_enable (struct snd_soc_component*) ; 

__attribute__((used)) static int bg_event(struct snd_soc_dapm_widget *w,
		    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	int ret = 0;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		wm8996_bg_enable(component);
		break;
	case SND_SOC_DAPM_POST_PMD:
		wm8996_bg_disable(component);
		break;
	default:
		WARN(1, "Invalid event %d\n", event);
		ret = -EINVAL;
	}

	return ret;
}