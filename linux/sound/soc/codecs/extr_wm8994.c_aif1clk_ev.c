#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm8994_priv {int* channels; struct wm8994* wm8994; } ;
struct wm8994 {int type; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  SND_SOC_DAPM_POST_PMD 133 
#define  SND_SOC_DAPM_POST_PMU 132 
#define  SND_SOC_DAPM_PRE_PMD 131 
#define  SND_SOC_DAPM_PRE_PMU 130 
#define  WM8958 129 
#define  WM8994 128 
 int WM8994_AIF1ADC1L_ENA ; 
 int WM8994_AIF1ADC1R_ENA ; 
 int WM8994_AIF1ADC2L_ENA ; 
 int WM8994_AIF1ADC2R_ENA ; 
 int WM8994_AIF1ADCL_SRC ; 
 int WM8994_AIF1ADCR_SRC ; 
 int WM8994_AIF1DAC1L_ENA ; 
 int WM8994_AIF1DAC1R_ENA ; 
 int WM8994_AIF1DAC2L_ENA ; 
 int WM8994_AIF1DAC2R_ENA ; 
 int WM8994_AIF1DACL_SRC ; 
 int WM8994_AIF1DACR_SRC ; 
 int WM8994_AIF1DSPCLK_ENA ; 
 int /*<<< orphan*/  WM8994_AIF1_CONTROL_1 ; 
 int /*<<< orphan*/  WM8994_AIF1_CONTROL_2 ; 
 int WM8994_AIF2DSPCLK_ENA ; 
 int /*<<< orphan*/  WM8994_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8994_POWER_MANAGEMENT_4 ; 
 int /*<<< orphan*/  WM8994_POWER_MANAGEMENT_5 ; 
 int WM8994_SYSDSPCLK_ENA ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 TYPE_1__* wm8994_vu_bits ; 

__attribute__((used)) static int aif1clk_ev(struct snd_soc_dapm_widget *w,
		      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int mask = WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC1R_ENA;
	int i;
	int dac;
	int adc;
	int val;

	switch (control->type) {
	case WM8994:
	case WM8958:
		mask |= WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA;
		break;
	default:
		break;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Don't enable timeslot 2 if not in use */
		if (wm8994->channels[0] <= 2)
			mask &= ~(WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA);

		val = snd_soc_component_read32(component, WM8994_AIF1_CONTROL_1);
		if ((val & WM8994_AIF1ADCL_SRC) &&
		    (val & WM8994_AIF1ADCR_SRC))
			adc = WM8994_AIF1ADC1R_ENA | WM8994_AIF1ADC2R_ENA;
		else if (!(val & WM8994_AIF1ADCL_SRC) &&
			 !(val & WM8994_AIF1ADCR_SRC))
			adc = WM8994_AIF1ADC1L_ENA | WM8994_AIF1ADC2L_ENA;
		else
			adc = WM8994_AIF1ADC1R_ENA | WM8994_AIF1ADC2R_ENA |
				WM8994_AIF1ADC1L_ENA | WM8994_AIF1ADC2L_ENA;

		val = snd_soc_component_read32(component, WM8994_AIF1_CONTROL_2);
		if ((val & WM8994_AIF1DACL_SRC) &&
		    (val & WM8994_AIF1DACR_SRC))
			dac = WM8994_AIF1DAC1R_ENA | WM8994_AIF1DAC2R_ENA;
		else if (!(val & WM8994_AIF1DACL_SRC) &&
			 !(val & WM8994_AIF1DACR_SRC))
			dac = WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC2L_ENA;
		else
			dac = WM8994_AIF1DAC1R_ENA | WM8994_AIF1DAC2R_ENA |
				WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC2L_ENA;

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    mask, adc);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    mask, dac);
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_AIF1DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA,
				    WM8994_AIF1DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4, mask,
				    WM8994_AIF1ADC1R_ENA |
				    WM8994_AIF1ADC1L_ENA |
				    WM8994_AIF1ADC2R_ENA |
				    WM8994_AIF1ADC2L_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5, mask,
				    WM8994_AIF1DAC1R_ENA |
				    WM8994_AIF1DAC1L_ENA |
				    WM8994_AIF1DAC2R_ENA |
				    WM8994_AIF1DAC2L_ENA);
		break;

	case SND_SOC_DAPM_POST_PMU:
		for (i = 0; i < ARRAY_SIZE(wm8994_vu_bits); i++)
			snd_soc_component_write(component, wm8994_vu_bits[i].reg,
				      snd_soc_component_read32(component,
						   wm8994_vu_bits[i].reg));
		break;

	case SND_SOC_DAPM_PRE_PMD:
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    mask, 0);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    mask, 0);

		val = snd_soc_component_read32(component, WM8994_CLOCKING_1);
		if (val & WM8994_AIF2DSPCLK_ENA)
			val = WM8994_SYSDSPCLK_ENA;
		else
			val = 0;
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_SYSDSPCLK_ENA |
				    WM8994_AIF1DSPCLK_ENA, val);
		break;
	}

	return 0;
}