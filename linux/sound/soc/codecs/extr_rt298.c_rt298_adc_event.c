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
struct snd_soc_dapm_widget {int reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
#define  RT298_ADC_IN1 131 
#define  RT298_ADC_IN2 130 
 int /*<<< orphan*/  RT298_D_FILTER_CTRL ; 
 int /*<<< orphan*/  RT298_VAD_CTRL ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  VERB_CMD (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt298_adc_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int nid;

	nid = (w->reg >> 20) & 0xff;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component,
			VERB_CMD(AC_VERB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7000);
		 /* If MCLK doesn't exist, reset AD filter */
		if (!(snd_soc_component_read32(component, RT298_VAD_CTRL) & 0x200)) {
			pr_info("NO MCLK\n");
			switch (nid) {
			case RT298_ADC_IN1:
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x2, 0x2);
				mdelay(10);
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x2, 0x0);
				break;
			case RT298_ADC_IN2:
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x4, 0x4);
				mdelay(10);
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x4, 0x0);
				break;
			}
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component,
			VERB_CMD(AC_VERB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7080);
		break;
	default:
		return 0;
	}

	return 0;
}