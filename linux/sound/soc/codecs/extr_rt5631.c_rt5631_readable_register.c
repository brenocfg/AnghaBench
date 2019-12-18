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
struct device {int dummy; } ;

/* Variables and functions */
#define  RT5631_ADC_CTRL_1 177 
#define  RT5631_ADC_CTRL_2 176 
#define  RT5631_ADC_REC_MIXER 175 
#define  RT5631_ALC_CTRL_1 174 
#define  RT5631_ALC_CTRL_2 173 
#define  RT5631_ALC_CTRL_3 172 
#define  RT5631_AUX_IN_VOL 171 
#define  RT5631_AXO1MIXER_CTRL 170 
#define  RT5631_AXO2MIXER_CTRL 169 
#define  RT5631_DEPOP_FUN_CTRL_1 168 
#define  RT5631_DEPOP_FUN_CTRL_2 167 
#define  RT5631_DIG_MIC_CTRL 166 
#define  RT5631_EQ_CTRL 165 
#define  RT5631_GEN_PUR_CTRL_REG 164 
#define  RT5631_GLOBAL_CLK_CTRL 163 
#define  RT5631_GPIO_CTRL 162 
#define  RT5631_HP_OUT_VOL 161 
#define  RT5631_INDEX_ADD 160 
#define  RT5631_INDEX_DATA 159 
#define  RT5631_INT_ST_IRQ_CTRL_1 158 
#define  RT5631_INT_ST_IRQ_CTRL_2 157 
#define  RT5631_JACK_DET_CTRL 156 
#define  RT5631_MIC_CTRL_1 155 
#define  RT5631_MIC_CTRL_2 154 
#define  RT5631_MISC_CTRL 153 
#define  RT5631_MONO_AXO_1_2_VOL 152 
#define  RT5631_MONO_INPUT_VOL 151 
#define  RT5631_MONO_SDP_CTRL 150 
#define  RT5631_OUTMIXER_L_CTRL 149 
#define  RT5631_OUTMIXER_R_CTRL 148 
#define  RT5631_PLL_CTRL 147 
#define  RT5631_PSEUDO_SPATL_CTRL 146 
#define  RT5631_PWR_MANAG_ADD1 145 
#define  RT5631_PWR_MANAG_ADD2 144 
#define  RT5631_PWR_MANAG_ADD3 143 
#define  RT5631_PWR_MANAG_ADD4 142 
#define  RT5631_RESET 141 
#define  RT5631_SDP_CTRL 140 
#define  RT5631_SOFT_VOL_CTRL 139 
#define  RT5631_SPK_MIXER_CTRL 138 
#define  RT5631_SPK_MONO_HP_OUT_CTRL 137 
#define  RT5631_SPK_MONO_OUT_CTRL 136 
#define  RT5631_SPK_OUT_VOL 135 
#define  RT5631_STEREO_AD_DA_CLK_CTRL 134 
#define  RT5631_STEREO_DAC_VOL_1 133 
#define  RT5631_STEREO_DAC_VOL_2 132 
#define  RT5631_VDAC_DIG_VOL 131 
#define  RT5631_VENDOR_ID 130 
#define  RT5631_VENDOR_ID1 129 
#define  RT5631_VENDOR_ID2 128 

__attribute__((used)) static bool rt5631_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT5631_RESET:
	case RT5631_SPK_OUT_VOL:
	case RT5631_HP_OUT_VOL:
	case RT5631_MONO_AXO_1_2_VOL:
	case RT5631_AUX_IN_VOL:
	case RT5631_STEREO_DAC_VOL_1:
	case RT5631_MIC_CTRL_1:
	case RT5631_STEREO_DAC_VOL_2:
	case RT5631_ADC_CTRL_1:
	case RT5631_ADC_REC_MIXER:
	case RT5631_ADC_CTRL_2:
	case RT5631_VDAC_DIG_VOL:
	case RT5631_OUTMIXER_L_CTRL:
	case RT5631_OUTMIXER_R_CTRL:
	case RT5631_AXO1MIXER_CTRL:
	case RT5631_AXO2MIXER_CTRL:
	case RT5631_MIC_CTRL_2:
	case RT5631_DIG_MIC_CTRL:
	case RT5631_MONO_INPUT_VOL:
	case RT5631_SPK_MIXER_CTRL:
	case RT5631_SPK_MONO_OUT_CTRL:
	case RT5631_SPK_MONO_HP_OUT_CTRL:
	case RT5631_SDP_CTRL:
	case RT5631_MONO_SDP_CTRL:
	case RT5631_STEREO_AD_DA_CLK_CTRL:
	case RT5631_PWR_MANAG_ADD1:
	case RT5631_PWR_MANAG_ADD2:
	case RT5631_PWR_MANAG_ADD3:
	case RT5631_PWR_MANAG_ADD4:
	case RT5631_GEN_PUR_CTRL_REG:
	case RT5631_GLOBAL_CLK_CTRL:
	case RT5631_PLL_CTRL:
	case RT5631_INT_ST_IRQ_CTRL_1:
	case RT5631_INT_ST_IRQ_CTRL_2:
	case RT5631_GPIO_CTRL:
	case RT5631_MISC_CTRL:
	case RT5631_DEPOP_FUN_CTRL_1:
	case RT5631_DEPOP_FUN_CTRL_2:
	case RT5631_JACK_DET_CTRL:
	case RT5631_SOFT_VOL_CTRL:
	case RT5631_ALC_CTRL_1:
	case RT5631_ALC_CTRL_2:
	case RT5631_ALC_CTRL_3:
	case RT5631_PSEUDO_SPATL_CTRL:
	case RT5631_INDEX_ADD:
	case RT5631_INDEX_DATA:
	case RT5631_EQ_CTRL:
	case RT5631_VENDOR_ID:
	case RT5631_VENDOR_ID1:
	case RT5631_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}