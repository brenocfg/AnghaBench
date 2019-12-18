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
struct snd_soc_dapm_widget {int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct pm8916_wcd_analog_priv {int /*<<< orphan*/  micbias2_cap_mode; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  pm8916_mbhc_configure_bias (struct pm8916_wcd_analog_priv*,int) ; 
 int pm8916_wcd_analog_enable_micbias_int (struct snd_soc_component*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pm8916_wcd_analog_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm8916_wcd_analog_enable_micbias_int2(struct
						  snd_soc_dapm_widget
						  *w, struct snd_kcontrol
						  *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		pm8916_mbhc_configure_bias(wcd, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		pm8916_mbhc_configure_bias(wcd, false);
		break;
	}

	return pm8916_wcd_analog_enable_micbias_int(component, event, w->reg,
						     wcd->micbias2_cap_mode);
}