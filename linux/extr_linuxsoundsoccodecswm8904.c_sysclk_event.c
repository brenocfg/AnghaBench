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
struct wm8904_priv {int /*<<< orphan*/  sysclk_src; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_PRE_PMU 129 
#define  WM8904_CLK_FLL 128 
 int /*<<< orphan*/  WM8904_FLL_CONTROL_1 ; 
 int WM8904_FLL_ENA ; 
 int WM8904_FLL_OSC_ENA ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysclk_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* If we're using the FLL then we only start it when
		 * required; we assume that the configuration has been
		 * done previously and all we need to do is kick it
		 * off.
		 */
		switch (wm8904->sysclk_src) {
		case WM8904_CLK_FLL:
			snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
					    WM8904_FLL_OSC_ENA,
					    WM8904_FLL_OSC_ENA);

			snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
					    WM8904_FLL_ENA,
					    WM8904_FLL_ENA);
			break;

		default:
			break;
		}
		break;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
				    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);
		break;
	}

	return 0;
}