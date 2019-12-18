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
typedef  int u8 ;
struct wcd9335_codec {int hph_l_gain; int hph_r_gain; int /*<<< orphan*/  component; scalar_t__* comp_enabled; } ;

/* Variables and functions */
#define  CLS_H_HIFI 131 
#define  CLS_H_LOHIFI 130 
 size_t COMPANDER_1 ; 
 size_t COMPANDER_2 ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WCD9335_HPH_AUTO_CHOP ; 
 int WCD9335_HPH_AUTO_CHOP_ENABLE_BY_CMPDR_GAIN ; 
 int WCD9335_HPH_AUTO_CHOP_FORCE_ENABLE ; 
 int /*<<< orphan*/  WCD9335_HPH_AUTO_CHOP_MASK ; 
 int WCD9335_HPH_GAIN_SRC_SEL_COMPANDER ; 
 int /*<<< orphan*/  WCD9335_HPH_GAIN_SRC_SEL_MASK ; 
 int /*<<< orphan*/  WCD9335_HPH_L_EN ; 
 int /*<<< orphan*/  WCD9335_HPH_PA_CTL1 ; 
 int /*<<< orphan*/  WCD9335_HPH_PA_GAIN_MASK ; 
 int /*<<< orphan*/  WCD9335_HPH_PA_GM3_IB_SCALE_MASK ; 
 int /*<<< orphan*/  WCD9335_HPH_R_EN ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wcd9335_codec_hph_post_pa_config(struct wcd9335_codec *wcd,
					     int mode, int event)
{
	u8 scale_val = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		switch (mode) {
		case CLS_H_HIFI:
			scale_val = 0x3;
			break;
		case CLS_H_LOHIFI:
			scale_val = 0x1;
			break;
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		scale_val = 0x6;
		break;
	}

	if (scale_val)
		snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_PA_CTL1,
					WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
					scale_val << 1);
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		if (wcd->comp_enabled[COMPANDER_1] ||
		    wcd->comp_enabled[COMPANDER_2]) {
			/* GAIN Source Selection */
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_L_EN,
					WCD9335_HPH_GAIN_SRC_SEL_MASK,
					WCD9335_HPH_GAIN_SRC_SEL_COMPANDER);
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_R_EN,
					WCD9335_HPH_GAIN_SRC_SEL_MASK,
					WCD9335_HPH_GAIN_SRC_SEL_COMPANDER);
			snd_soc_component_update_bits(wcd->component,
					WCD9335_HPH_AUTO_CHOP,
					WCD9335_HPH_AUTO_CHOP_MASK,
					WCD9335_HPH_AUTO_CHOP_FORCE_ENABLE);
		}
		snd_soc_component_update_bits(wcd->component,
						WCD9335_HPH_L_EN,
						WCD9335_HPH_PA_GAIN_MASK,
						wcd->hph_l_gain);
		snd_soc_component_update_bits(wcd->component,
						WCD9335_HPH_R_EN,
						WCD9335_HPH_PA_GAIN_MASK,
						wcd->hph_r_gain);
	}

	if (SND_SOC_DAPM_EVENT_OFF(event))
		snd_soc_component_update_bits(wcd->component,
				WCD9335_HPH_AUTO_CHOP,
				WCD9335_HPH_AUTO_CHOP_MASK,
				WCD9335_HPH_AUTO_CHOP_ENABLE_BY_CMPDR_GAIN);
}