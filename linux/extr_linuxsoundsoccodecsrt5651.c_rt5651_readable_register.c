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
struct TYPE_3__ {unsigned int window_start; unsigned int window_len; unsigned int range_min; unsigned int range_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  RT5651_ADC_BST_VOL 227 
#define  RT5651_ADC_DATA 226 
#define  RT5651_ADC_DIG_VOL 225 
#define  RT5651_ADDA_CLK1 224 
#define  RT5651_ADDA_CLK2 223 
#define  RT5651_ADJ_HPF_CTRL1 222 
#define  RT5651_ADJ_HPF_CTRL2 221 
#define  RT5651_AD_DA_MIXER 220 
#define  RT5651_ALC_1 219 
#define  RT5651_ALC_2 218 
#define  RT5651_ALC_3 217 
#define  RT5651_A_JD_CTL1 216 
#define  RT5651_BASE_BACK 215 
#define  RT5651_CHARGE_PUMP 214 
#define  RT5651_DAC1_DIG_VOL 213 
#define  RT5651_DAC2_CTRL 212 
#define  RT5651_DAC2_DIG_VOL 211 
#define  RT5651_DD_MIXER 210 
#define  RT5651_DEPOP_M1 209 
#define  RT5651_DEPOP_M2 208 
#define  RT5651_DEPOP_M3 207 
#define  RT5651_DEVICE_ID 206 
#define  RT5651_DIG_INF_DATA 205 
#define  RT5651_DMIC 204 
#define  RT5651_DUMMY2 203 
#define  RT5651_DUMMY3 202 
#define  RT5651_D_MISC 201 
#define  RT5651_EQ_CTRL1 200 
#define  RT5651_EQ_CTRL2 199 
#define  RT5651_GLB_CLK 198 
#define  RT5651_GPIO_CTRL1 197 
#define  RT5651_GPIO_CTRL2 196 
#define  RT5651_GPIO_CTRL3 195 
#define  RT5651_HPO_MIXER 194 
#define  RT5651_HP_CALIB2 193 
#define  RT5651_HP_CALIB_AMP_DET 192 
#define  RT5651_HP_VOL 191 
#define  RT5651_I2S1_SDP 190 
#define  RT5651_I2S2_SDP 189 
#define  RT5651_IN1_IN2 188 
#define  RT5651_IN3 187 
#define  RT5651_INL1_INR1_VOL 186 
#define  RT5651_INL2_INR2_VOL 185 
#define  RT5651_INT_IRQ_ST 184 
#define  RT5651_IRQ_CTRL1 183 
#define  RT5651_IRQ_CTRL2 182 
#define  RT5651_JD_CTRL1 181 
#define  RT5651_JD_CTRL2 180 
#define  RT5651_LOUT_CTRL1 179 
#define  RT5651_LOUT_CTRL2 178 
#define  RT5651_LOUT_MIXER 177 
#define  RT5651_MICBIAS 176 
#define  RT5651_MP3_PLUS1 175 
#define  RT5651_MP3_PLUS2 174 
#define  RT5651_OUT_L1_MIXER 173 
#define  RT5651_OUT_L2_MIXER 172 
#define  RT5651_OUT_L3_MIXER 171 
#define  RT5651_OUT_R1_MIXER 170 
#define  RT5651_OUT_R2_MIXER 169 
#define  RT5651_OUT_R3_MIXER 168 
#define  RT5651_PDM_CTL 167 
#define  RT5651_PGM_REG_ARR1 166 
#define  RT5651_PGM_REG_ARR2 165 
#define  RT5651_PGM_REG_ARR3 164 
#define  RT5651_PGM_REG_ARR4 163 
#define  RT5651_PGM_REG_ARR5 162 
#define  RT5651_PLL_CTRL1 161 
#define  RT5651_PLL_CTRL2 160 
#define  RT5651_PLL_MODE_1 159 
#define  RT5651_PLL_MODE_2 158 
#define  RT5651_PLL_MODE_3 157 
#define  RT5651_PLL_MODE_4 156 
#define  RT5651_PLL_MODE_5 155 
#define  RT5651_PLL_MODE_6 154 
#define  RT5651_PLL_MODE_7 153 
#define  RT5651_PRIV_DATA 152 
#define  RT5651_PRIV_INDEX 151 
#define  RT5651_PWR_ANLG1 150 
#define  RT5651_PWR_ANLG2 149 
#define  RT5651_PWR_DIG1 148 
#define  RT5651_PWR_DIG2 147 
#define  RT5651_PWR_MIXER 146 
#define  RT5651_PWR_VOL 145 
#define  RT5651_REC_L1_MIXER 144 
#define  RT5651_REC_L2_MIXER 143 
#define  RT5651_REC_R1_MIXER 142 
#define  RT5651_REC_R2_MIXER 141 
#define  RT5651_RESET 140 
#define  RT5651_SCB_CTRL 139 
#define  RT5651_SCB_FUNC 138 
#define  RT5651_STO1_ADC_MIXER 137 
#define  RT5651_STO2_ADC_MIXER 136 
#define  RT5651_STO_DAC_MIXER 135 
#define  RT5651_SV_ZCD1 134 
#define  RT5651_SV_ZCD2 133 
#define  RT5651_TDM_CTL_1 132 
#define  RT5651_TDM_CTL_2 131 
#define  RT5651_TDM_CTL_3 130 
#define  RT5651_VENDOR_ID 129 
#define  RT5651_VERSION_ID 128 
 TYPE_1__* rt5651_ranges ; 

__attribute__((used)) static bool rt5651_readable_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5651_ranges); i++) {
		if ((reg >= rt5651_ranges[i].window_start &&
		     reg <= rt5651_ranges[i].window_start +
		     rt5651_ranges[i].window_len) ||
		    (reg >= rt5651_ranges[i].range_min &&
		     reg <= rt5651_ranges[i].range_max)) {
			return true;
		}
	}

	switch (reg) {
	case RT5651_RESET:
	case RT5651_VERSION_ID:
	case RT5651_VENDOR_ID:
	case RT5651_DEVICE_ID:
	case RT5651_HP_VOL:
	case RT5651_LOUT_CTRL1:
	case RT5651_LOUT_CTRL2:
	case RT5651_IN1_IN2:
	case RT5651_IN3:
	case RT5651_INL1_INR1_VOL:
	case RT5651_INL2_INR2_VOL:
	case RT5651_DAC1_DIG_VOL:
	case RT5651_DAC2_DIG_VOL:
	case RT5651_DAC2_CTRL:
	case RT5651_ADC_DIG_VOL:
	case RT5651_ADC_DATA:
	case RT5651_ADC_BST_VOL:
	case RT5651_STO1_ADC_MIXER:
	case RT5651_STO2_ADC_MIXER:
	case RT5651_AD_DA_MIXER:
	case RT5651_STO_DAC_MIXER:
	case RT5651_DD_MIXER:
	case RT5651_DIG_INF_DATA:
	case RT5651_PDM_CTL:
	case RT5651_REC_L1_MIXER:
	case RT5651_REC_L2_MIXER:
	case RT5651_REC_R1_MIXER:
	case RT5651_REC_R2_MIXER:
	case RT5651_HPO_MIXER:
	case RT5651_OUT_L1_MIXER:
	case RT5651_OUT_L2_MIXER:
	case RT5651_OUT_L3_MIXER:
	case RT5651_OUT_R1_MIXER:
	case RT5651_OUT_R2_MIXER:
	case RT5651_OUT_R3_MIXER:
	case RT5651_LOUT_MIXER:
	case RT5651_PWR_DIG1:
	case RT5651_PWR_DIG2:
	case RT5651_PWR_ANLG1:
	case RT5651_PWR_ANLG2:
	case RT5651_PWR_MIXER:
	case RT5651_PWR_VOL:
	case RT5651_PRIV_INDEX:
	case RT5651_PRIV_DATA:
	case RT5651_I2S1_SDP:
	case RT5651_I2S2_SDP:
	case RT5651_ADDA_CLK1:
	case RT5651_ADDA_CLK2:
	case RT5651_DMIC:
	case RT5651_TDM_CTL_1:
	case RT5651_TDM_CTL_2:
	case RT5651_TDM_CTL_3:
	case RT5651_GLB_CLK:
	case RT5651_PLL_CTRL1:
	case RT5651_PLL_CTRL2:
	case RT5651_PLL_MODE_1:
	case RT5651_PLL_MODE_2:
	case RT5651_PLL_MODE_3:
	case RT5651_PLL_MODE_4:
	case RT5651_PLL_MODE_5:
	case RT5651_PLL_MODE_6:
	case RT5651_PLL_MODE_7:
	case RT5651_DEPOP_M1:
	case RT5651_DEPOP_M2:
	case RT5651_DEPOP_M3:
	case RT5651_CHARGE_PUMP:
	case RT5651_MICBIAS:
	case RT5651_A_JD_CTL1:
	case RT5651_EQ_CTRL1:
	case RT5651_EQ_CTRL2:
	case RT5651_ALC_1:
	case RT5651_ALC_2:
	case RT5651_ALC_3:
	case RT5651_JD_CTRL1:
	case RT5651_JD_CTRL2:
	case RT5651_IRQ_CTRL1:
	case RT5651_IRQ_CTRL2:
	case RT5651_INT_IRQ_ST:
	case RT5651_GPIO_CTRL1:
	case RT5651_GPIO_CTRL2:
	case RT5651_GPIO_CTRL3:
	case RT5651_PGM_REG_ARR1:
	case RT5651_PGM_REG_ARR2:
	case RT5651_PGM_REG_ARR3:
	case RT5651_PGM_REG_ARR4:
	case RT5651_PGM_REG_ARR5:
	case RT5651_SCB_FUNC:
	case RT5651_SCB_CTRL:
	case RT5651_BASE_BACK:
	case RT5651_MP3_PLUS1:
	case RT5651_MP3_PLUS2:
	case RT5651_ADJ_HPF_CTRL1:
	case RT5651_ADJ_HPF_CTRL2:
	case RT5651_HP_CALIB_AMP_DET:
	case RT5651_HP_CALIB2:
	case RT5651_SV_ZCD1:
	case RT5651_SV_ZCD2:
	case RT5651_D_MISC:
	case RT5651_DUMMY2:
	case RT5651_DUMMY3:
		return true;
	default:
		return false;
	}
}