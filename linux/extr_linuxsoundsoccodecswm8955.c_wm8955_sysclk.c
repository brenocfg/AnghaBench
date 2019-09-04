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
 int /*<<< orphan*/  WM8955_CLOCKING_PLL ; 
 int WM8955_DIGENB ; 
 int WM8955_PLLEN ; 
 int WM8955_PLL_RB ; 
 int /*<<< orphan*/  WM8955_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int wm8955_configure_clocking (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8955_sysclk(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	int ret = 0;

	/* Always disable the clocks - if we're doing reconfiguration this
	 * avoids misclocking.
	 */
	snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
			    WM8955_DIGENB, 0);
	snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
			    WM8955_PLL_RB | WM8955_PLLEN, 0);

	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		break;
	case SND_SOC_DAPM_PRE_PMU:
		ret = wm8955_configure_clocking(component);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}