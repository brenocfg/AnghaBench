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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  WCD9335_HPH_CNP_WG_CTL ; 
 int WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK ; 
 int WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_1000 ; 
 int WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_500 ; 
 int WCD9335_HPH_CONST_SEL_L_HQ_PATH ; 
 int WCD9335_HPH_CONST_SEL_L_MASK ; 
 int /*<<< orphan*/  WCD9335_HPH_L_EN ; 
 int /*<<< orphan*/  WCD9335_HPH_PA_CTL1 ; 
 int /*<<< orphan*/  WCD9335_HPH_PA_CTL2 ; 
 int WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_DISABLE ; 
 int WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_ENABLE ; 
 int WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK ; 
 int WCD9335_HPH_PA_CTL2_FORCE_PSRREH_DISABLE ; 
 int WCD9335_HPH_PA_CTL2_FORCE_PSRREH_ENABLE ; 
 int WCD9335_HPH_PA_CTL2_FORCE_PSRREH_MASK ; 
 int WCD9335_HPH_PA_CTL2_HPH_PSRR_DISABLE ; 
 int WCD9335_HPH_PA_CTL2_HPH_PSRR_ENABLE ; 
 int WCD9335_HPH_PA_CTL2_HPH_PSRR_ENH_MASK ; 
 int WCD9335_HPH_PA_GM3_IB_SCALE_MASK ; 
 int WCD9335_HPH_RDAC_1P65_LD_OUTCTL_MASK ; 
 int WCD9335_HPH_RDAC_1P65_LD_OUTCTL_V_N1P60 ; 
 int /*<<< orphan*/  WCD9335_HPH_RDAC_LDO_CTL ; 
 int WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_MASK ; 
 int WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_V_N1P60 ; 
 int /*<<< orphan*/  WCD9335_HPH_R_EN ; 
 int /*<<< orphan*/  WCD9335_RX_BIAS_HPH_RDAC_LDO ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcd9335_codec_hph_mode_gain_opt (struct snd_soc_component*,int) ; 

__attribute__((used)) static void wcd9335_codec_hph_lp_config(struct snd_soc_component *comp,
				      int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL1,
				WCD9335_HPH_PA_GM3_IB_SCALE_MASK,
				0x0C);
		wcd9335_codec_hph_mode_gain_opt(comp, 0x10);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_1000);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
			WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENH_MASK,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_RDAC_LDO_CTL,
				WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_MASK,
				WCD9335_HPH_RDAC_N1P65_LD_OUTCTL_V_N1P60);
		snd_soc_component_update_bits(comp, WCD9335_HPH_RDAC_LDO_CTL,
				WCD9335_HPH_RDAC_1P65_LD_OUTCTL_MASK,
				WCD9335_HPH_RDAC_1P65_LD_OUTCTL_V_N1P60);
		snd_soc_component_update_bits(comp,
				WCD9335_RX_BIAS_HPH_RDAC_LDO, 0x0F, 0x01);
		snd_soc_component_update_bits(comp,
				WCD9335_RX_BIAS_HPH_RDAC_LDO, 0xF0, 0x10);
	}

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		snd_soc_component_write(comp, WCD9335_RX_BIAS_HPH_RDAC_LDO,
					0x88);
		snd_soc_component_write(comp, WCD9335_HPH_RDAC_LDO_CTL,
					0x33);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_ENH_MASK,
				WCD9335_HPH_PA_CTL2_HPH_PSRR_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_PSRREH_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_PA_CTL2,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_MASK,
				WCD9335_HPH_PA_CTL2_FORCE_IQCTRL_DISABLE);
		snd_soc_component_update_bits(comp, WCD9335_HPH_CNP_WG_CTL,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_MASK,
				WCD9335_HPH_CNP_WG_CTL_CURR_LDIV_RATIO_500);
		snd_soc_component_update_bits(comp, WCD9335_HPH_R_EN,
				WCD9335_HPH_CONST_SEL_L_MASK,
				WCD9335_HPH_CONST_SEL_L_HQ_PATH);
		snd_soc_component_update_bits(comp, WCD9335_HPH_L_EN,
				WCD9335_HPH_CONST_SEL_L_MASK,
				WCD9335_HPH_CONST_SEL_L_HQ_PATH);
	}
}