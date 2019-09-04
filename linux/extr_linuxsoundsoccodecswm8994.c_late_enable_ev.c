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
struct wm8994_priv {int /*<<< orphan*/  aif2clk_enable; int /*<<< orphan*/  aif1clk_enable; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int const SND_SOC_DAPM_POST_PMU ; 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WM8994_AIF1CLK_ENA ; 
 int /*<<< orphan*/  WM8994_AIF1CLK_ENA_MASK ; 
 int /*<<< orphan*/  WM8994_AIF1_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8994_AIF2CLK_ENA ; 
 int /*<<< orphan*/  WM8994_AIF2CLK_ENA_MASK ; 
 int /*<<< orphan*/  WM8994_AIF2_CLOCKING_1 ; 
 int /*<<< orphan*/  aif1clk_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int const) ; 
 int /*<<< orphan*/  aif2clk_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int const) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_aif_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 

__attribute__((used)) static int late_enable_ev(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (wm8994->aif1clk_enable) {
			aif1clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMU);
			snd_soc_component_update_bits(component, WM8994_AIF1_CLOCKING_1,
					    WM8994_AIF1CLK_ENA_MASK,
					    WM8994_AIF1CLK_ENA);
			aif1clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMU);
			wm8994->aif1clk_enable = 0;
		}
		if (wm8994->aif2clk_enable) {
			aif2clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMU);
			snd_soc_component_update_bits(component, WM8994_AIF2_CLOCKING_1,
					    WM8994_AIF2CLK_ENA_MASK,
					    WM8994_AIF2CLK_ENA);
			aif2clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMU);
			wm8994->aif2clk_enable = 0;
		}
		break;
	}

	/* We may also have postponed startup of DSP, handle that. */
	wm8958_aif_ev(w, kcontrol, event);

	return 0;
}