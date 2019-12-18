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
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int range_min; unsigned int range_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  RT5616_ADC_BST_VOL 211 
#define  RT5616_ADC_DIG_VOL 210 
#define  RT5616_ADDA_CLK1 209 
#define  RT5616_ADDA_CLK2 208 
#define  RT5616_ADJ_HPF_CTRL1 207 
#define  RT5616_ADJ_HPF_CTRL2 206 
#define  RT5616_AD_DA_MIXER 205 
#define  RT5616_A_JD_CTL1 204 
#define  RT5616_A_JD_CTL2 203 
#define  RT5616_BASE_BACK 202 
#define  RT5616_CHARGE_PUMP 201 
#define  RT5616_DAC1_DIG_VOL 200 
#define  RT5616_DEPOP_M1 199 
#define  RT5616_DEPOP_M2 198 
#define  RT5616_DEPOP_M3 197 
#define  RT5616_DEVICE_ID 196 
#define  RT5616_DRC_AGC_1 195 
#define  RT5616_DRC_AGC_2 194 
#define  RT5616_DRC_AGC_3 193 
#define  RT5616_DUMMY2 192 
#define  RT5616_DUMMY3 191 
#define  RT5616_D_MISC 190 
#define  RT5616_EQ_CTRL1 189 
#define  RT5616_EQ_CTRL2 188 
#define  RT5616_GLB_CLK 187 
#define  RT5616_GPIO_CTRL1 186 
#define  RT5616_GPIO_CTRL2 185 
#define  RT5616_GPIO_CTRL3 184 
#define  RT5616_HPO_MIXER 183 
#define  RT5616_HP_CALIB2 182 
#define  RT5616_HP_CALIB_AMP_DET 181 
#define  RT5616_HP_OVCD 180 
#define  RT5616_HP_VOL 179 
#define  RT5616_I2S1_SDP 178 
#define  RT5616_IN1_IN2 177 
#define  RT5616_INL1_INR1_VOL 176 
#define  RT5616_INT_IRQ_ST 175 
#define  RT5616_IRQ_CTRL1 174 
#define  RT5616_IRQ_CTRL2 173 
#define  RT5616_JD_CTRL1 172 
#define  RT5616_JD_CTRL2 171 
#define  RT5616_LOUT_CTRL1 170 
#define  RT5616_LOUT_CTRL2 169 
#define  RT5616_LOUT_MIXER 168 
#define  RT5616_MICBIAS 167 
#define  RT5616_MP3_PLUS1 166 
#define  RT5616_MP3_PLUS2 165 
#define  RT5616_OUT_L1_MIXER 164 
#define  RT5616_OUT_L2_MIXER 163 
#define  RT5616_OUT_L3_MIXER 162 
#define  RT5616_OUT_R1_MIXER 161 
#define  RT5616_OUT_R2_MIXER 160 
#define  RT5616_OUT_R3_MIXER 159 
#define  RT5616_PGM_REG_ARR1 158 
#define  RT5616_PGM_REG_ARR2 157 
#define  RT5616_PGM_REG_ARR3 156 
#define  RT5616_PGM_REG_ARR4 155 
#define  RT5616_PGM_REG_ARR5 154 
#define  RT5616_PLL_CTRL1 153 
#define  RT5616_PLL_CTRL2 152 
#define  RT5616_PRIV_DATA 151 
#define  RT5616_PRIV_INDEX 150 
#define  RT5616_PV_DET_SPK_G 149 
#define  RT5616_PWR_ANLG1 148 
#define  RT5616_PWR_ANLG2 147 
#define  RT5616_PWR_DIG1 146 
#define  RT5616_PWR_DIG2 145 
#define  RT5616_PWR_MIXER 144 
#define  RT5616_PWR_VOL 143 
#define  RT5616_REC_L1_MIXER 142 
#define  RT5616_REC_L2_MIXER 141 
#define  RT5616_REC_R1_MIXER 140 
#define  RT5616_REC_R2_MIXER 139 
#define  RT5616_RESET 138 
#define  RT5616_SCB_CTRL 137 
#define  RT5616_SCB_FUNC 136 
#define  RT5616_STO1_ADC_MIXER 135 
#define  RT5616_STO_DAC_MIXER 134 
#define  RT5616_SVOL_ZC 133 
#define  RT5616_SV_ZCD1 132 
#define  RT5616_SV_ZCD2 131 
#define  RT5616_VENDOR_ID 130 
#define  RT5616_VERSION_ID 129 
#define  RT5616_WIND_FILTER 128 
 TYPE_1__* rt5616_ranges ; 

__attribute__((used)) static bool rt5616_readable_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5616_ranges); i++) {
		if (reg >= rt5616_ranges[i].range_min &&
		    reg <= rt5616_ranges[i].range_max)
			return true;
	}

	switch (reg) {
	case RT5616_RESET:
	case RT5616_VERSION_ID:
	case RT5616_VENDOR_ID:
	case RT5616_DEVICE_ID:
	case RT5616_HP_VOL:
	case RT5616_LOUT_CTRL1:
	case RT5616_LOUT_CTRL2:
	case RT5616_IN1_IN2:
	case RT5616_INL1_INR1_VOL:
	case RT5616_DAC1_DIG_VOL:
	case RT5616_ADC_DIG_VOL:
	case RT5616_ADC_BST_VOL:
	case RT5616_STO1_ADC_MIXER:
	case RT5616_AD_DA_MIXER:
	case RT5616_STO_DAC_MIXER:
	case RT5616_REC_L1_MIXER:
	case RT5616_REC_L2_MIXER:
	case RT5616_REC_R1_MIXER:
	case RT5616_REC_R2_MIXER:
	case RT5616_HPO_MIXER:
	case RT5616_OUT_L1_MIXER:
	case RT5616_OUT_L2_MIXER:
	case RT5616_OUT_L3_MIXER:
	case RT5616_OUT_R1_MIXER:
	case RT5616_OUT_R2_MIXER:
	case RT5616_OUT_R3_MIXER:
	case RT5616_LOUT_MIXER:
	case RT5616_PWR_DIG1:
	case RT5616_PWR_DIG2:
	case RT5616_PWR_ANLG1:
	case RT5616_PWR_ANLG2:
	case RT5616_PWR_MIXER:
	case RT5616_PWR_VOL:
	case RT5616_PRIV_INDEX:
	case RT5616_PRIV_DATA:
	case RT5616_I2S1_SDP:
	case RT5616_ADDA_CLK1:
	case RT5616_ADDA_CLK2:
	case RT5616_GLB_CLK:
	case RT5616_PLL_CTRL1:
	case RT5616_PLL_CTRL2:
	case RT5616_HP_OVCD:
	case RT5616_DEPOP_M1:
	case RT5616_DEPOP_M2:
	case RT5616_DEPOP_M3:
	case RT5616_CHARGE_PUMP:
	case RT5616_PV_DET_SPK_G:
	case RT5616_MICBIAS:
	case RT5616_A_JD_CTL1:
	case RT5616_A_JD_CTL2:
	case RT5616_EQ_CTRL1:
	case RT5616_EQ_CTRL2:
	case RT5616_WIND_FILTER:
	case RT5616_DRC_AGC_1:
	case RT5616_DRC_AGC_2:
	case RT5616_DRC_AGC_3:
	case RT5616_SVOL_ZC:
	case RT5616_JD_CTRL1:
	case RT5616_JD_CTRL2:
	case RT5616_IRQ_CTRL1:
	case RT5616_IRQ_CTRL2:
	case RT5616_INT_IRQ_ST:
	case RT5616_GPIO_CTRL1:
	case RT5616_GPIO_CTRL2:
	case RT5616_GPIO_CTRL3:
	case RT5616_PGM_REG_ARR1:
	case RT5616_PGM_REG_ARR2:
	case RT5616_PGM_REG_ARR3:
	case RT5616_PGM_REG_ARR4:
	case RT5616_PGM_REG_ARR5:
	case RT5616_SCB_FUNC:
	case RT5616_SCB_CTRL:
	case RT5616_BASE_BACK:
	case RT5616_MP3_PLUS1:
	case RT5616_MP3_PLUS2:
	case RT5616_ADJ_HPF_CTRL1:
	case RT5616_ADJ_HPF_CTRL2:
	case RT5616_HP_CALIB_AMP_DET:
	case RT5616_HP_CALIB2:
	case RT5616_SV_ZCD1:
	case RT5616_SV_ZCD2:
	case RT5616_D_MISC:
	case RT5616_DUMMY2:
	case RT5616_DUMMY3:
		return true;
	default:
		return false;
	}
}