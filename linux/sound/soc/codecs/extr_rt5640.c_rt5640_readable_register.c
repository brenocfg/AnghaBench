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
#define  RT5640_3D_HP 242 
#define  RT5640_ADC_BST_VOL 241 
#define  RT5640_ADC_DATA 240 
#define  RT5640_ADC_DIG_VOL 239 
#define  RT5640_ADDA_CLK1 238 
#define  RT5640_ADDA_CLK2 237 
#define  RT5640_ADJ_HPF 236 
#define  RT5640_AD_DA_MIXER 235 
#define  RT5640_ANC_CTRL1 234 
#define  RT5640_ANC_CTRL2 233 
#define  RT5640_ANC_CTRL3 232 
#define  RT5640_ANC_JD 231 
#define  RT5640_ASRC_1 230 
#define  RT5640_ASRC_2 229 
#define  RT5640_ASRC_3 228 
#define  RT5640_ASRC_4 227 
#define  RT5640_ASRC_5 226 
#define  RT5640_BASE_BACK 225 
#define  RT5640_CHARGE_PUMP 224 
#define  RT5640_CLS_D_OUT 223 
#define  RT5640_CLS_D_OVCD 222 
#define  RT5640_DAC1_DIG_VOL 221 
#define  RT5640_DAC2_CTRL 220 
#define  RT5640_DAC2_DIG_VOL 219 
#define  RT5640_DEPOP_M1 218 
#define  RT5640_DEPOP_M2 217 
#define  RT5640_DEPOP_M3 216 
#define  RT5640_DIG_INF_DATA 215 
#define  RT5640_DIG_MIXER 214 
#define  RT5640_DMIC 213 
#define  RT5640_DRC_AGC_1 212 
#define  RT5640_DRC_AGC_2 211 
#define  RT5640_DRC_AGC_3 210 
#define  RT5640_DSP_CTRL1 209 
#define  RT5640_DSP_CTRL2 208 
#define  RT5640_DSP_CTRL3 207 
#define  RT5640_DSP_CTRL4 206 
#define  RT5640_DSP_PATH1 205 
#define  RT5640_DSP_PATH2 204 
#define  RT5640_DUMMY1 203 
#define  RT5640_DUMMY2 202 
#define  RT5640_DUMMY3 201 
#define  RT5640_EQ_CTRL1 200 
#define  RT5640_EQ_CTRL2 199 
#define  RT5640_GLB_CLK 198 
#define  RT5640_GPIO_CTRL1 197 
#define  RT5640_GPIO_CTRL2 196 
#define  RT5640_GPIO_CTRL3 195 
#define  RT5640_HPO_MIXER 194 
#define  RT5640_HP_CALIB2 193 
#define  RT5640_HP_CALIB_AMP_DET 192 
#define  RT5640_HP_OVCD 191 
#define  RT5640_HP_VOL 190 
#define  RT5640_I2S1_SDP 189 
#define  RT5640_I2S2_SDP 188 
#define  RT5640_IN1_IN2 187 
#define  RT5640_IN3_IN4 186 
#define  RT5640_INL_INR_VOL 185 
#define  RT5640_INT_IRQ_ST 184 
#define  RT5640_IRQ_CTRL1 183 
#define  RT5640_IRQ_CTRL2 182 
#define  RT5640_JD_CTRL 181 
#define  RT5640_LOUT_MIXER 180 
#define  RT5640_MICBIAS 179 
#define  RT5640_MONO_ADC_MIXER 178 
#define  RT5640_MONO_DAC_MIXER 177 
#define  RT5640_MONO_MIXER 176 
#define  RT5640_MONO_OUT 175 
#define  RT5640_MP3_PLUS1 174 
#define  RT5640_MP3_PLUS2 173 
#define  RT5640_OUTPUT 172 
#define  RT5640_OUT_L1_MIXER 171 
#define  RT5640_OUT_L2_MIXER 170 
#define  RT5640_OUT_L3_MIXER 169 
#define  RT5640_OUT_R1_MIXER 168 
#define  RT5640_OUT_R2_MIXER 167 
#define  RT5640_OUT_R3_MIXER 166 
#define  RT5640_PGM_REG_ARR1 165 
#define  RT5640_PGM_REG_ARR2 164 
#define  RT5640_PGM_REG_ARR3 163 
#define  RT5640_PGM_REG_ARR4 162 
#define  RT5640_PGM_REG_ARR5 161 
#define  RT5640_PLL_CTRL1 160 
#define  RT5640_PLL_CTRL2 159 
#define  RT5640_PRIV_DATA 158 
#define  RT5640_PRIV_INDEX 157 
#define  RT5640_PV_DET_SPK_G 156 
#define  RT5640_PWR_ANLG1 155 
#define  RT5640_PWR_ANLG2 154 
#define  RT5640_PWR_DIG1 153 
#define  RT5640_PWR_DIG2 152 
#define  RT5640_PWR_MIXER 151 
#define  RT5640_PWR_VOL 150 
#define  RT5640_REC_L1_MIXER 149 
#define  RT5640_REC_L2_MIXER 148 
#define  RT5640_REC_R1_MIXER 147 
#define  RT5640_REC_R2_MIXER 146 
#define  RT5640_RESET 145 
#define  RT5640_SCB_CTRL 144 
#define  RT5640_SCB_FUNC 143 
#define  RT5640_SPK_L_MIXER 142 
#define  RT5640_SPK_R_MIXER 141 
#define  RT5640_SPK_VOL 140 
#define  RT5640_SPO_CLSD_RATIO 139 
#define  RT5640_SPO_L_MIXER 138 
#define  RT5640_SPO_R_MIXER 137 
#define  RT5640_STO_ADC_MIXER 136 
#define  RT5640_STO_DAC_MIXER 135 
#define  RT5640_SVOL_ZC 134 
#define  RT5640_SV_ZCD1 133 
#define  RT5640_SV_ZCD2 132 
#define  RT5640_VENDOR_ID 131 
#define  RT5640_VENDOR_ID1 130 
#define  RT5640_VENDOR_ID2 129 
#define  RT5640_WIND_FILTER 128 
 TYPE_1__* rt5640_ranges ; 

__attribute__((used)) static bool rt5640_readable_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5640_ranges); i++)
		if ((reg >= rt5640_ranges[i].window_start &&
		     reg <= rt5640_ranges[i].window_start +
		     rt5640_ranges[i].window_len) ||
		    (reg >= rt5640_ranges[i].range_min &&
		     reg <= rt5640_ranges[i].range_max))
			return true;

	switch (reg) {
	case RT5640_RESET:
	case RT5640_SPK_VOL:
	case RT5640_HP_VOL:
	case RT5640_OUTPUT:
	case RT5640_MONO_OUT:
	case RT5640_IN1_IN2:
	case RT5640_IN3_IN4:
	case RT5640_INL_INR_VOL:
	case RT5640_DAC1_DIG_VOL:
	case RT5640_DAC2_DIG_VOL:
	case RT5640_DAC2_CTRL:
	case RT5640_ADC_DIG_VOL:
	case RT5640_ADC_DATA:
	case RT5640_ADC_BST_VOL:
	case RT5640_STO_ADC_MIXER:
	case RT5640_MONO_ADC_MIXER:
	case RT5640_AD_DA_MIXER:
	case RT5640_STO_DAC_MIXER:
	case RT5640_MONO_DAC_MIXER:
	case RT5640_DIG_MIXER:
	case RT5640_DSP_PATH1:
	case RT5640_DSP_PATH2:
	case RT5640_DIG_INF_DATA:
	case RT5640_REC_L1_MIXER:
	case RT5640_REC_L2_MIXER:
	case RT5640_REC_R1_MIXER:
	case RT5640_REC_R2_MIXER:
	case RT5640_HPO_MIXER:
	case RT5640_SPK_L_MIXER:
	case RT5640_SPK_R_MIXER:
	case RT5640_SPO_L_MIXER:
	case RT5640_SPO_R_MIXER:
	case RT5640_SPO_CLSD_RATIO:
	case RT5640_MONO_MIXER:
	case RT5640_OUT_L1_MIXER:
	case RT5640_OUT_L2_MIXER:
	case RT5640_OUT_L3_MIXER:
	case RT5640_OUT_R1_MIXER:
	case RT5640_OUT_R2_MIXER:
	case RT5640_OUT_R3_MIXER:
	case RT5640_LOUT_MIXER:
	case RT5640_PWR_DIG1:
	case RT5640_PWR_DIG2:
	case RT5640_PWR_ANLG1:
	case RT5640_PWR_ANLG2:
	case RT5640_PWR_MIXER:
	case RT5640_PWR_VOL:
	case RT5640_PRIV_INDEX:
	case RT5640_PRIV_DATA:
	case RT5640_I2S1_SDP:
	case RT5640_I2S2_SDP:
	case RT5640_ADDA_CLK1:
	case RT5640_ADDA_CLK2:
	case RT5640_DMIC:
	case RT5640_GLB_CLK:
	case RT5640_PLL_CTRL1:
	case RT5640_PLL_CTRL2:
	case RT5640_ASRC_1:
	case RT5640_ASRC_2:
	case RT5640_ASRC_3:
	case RT5640_ASRC_4:
	case RT5640_ASRC_5:
	case RT5640_HP_OVCD:
	case RT5640_CLS_D_OVCD:
	case RT5640_CLS_D_OUT:
	case RT5640_DEPOP_M1:
	case RT5640_DEPOP_M2:
	case RT5640_DEPOP_M3:
	case RT5640_CHARGE_PUMP:
	case RT5640_PV_DET_SPK_G:
	case RT5640_MICBIAS:
	case RT5640_EQ_CTRL1:
	case RT5640_EQ_CTRL2:
	case RT5640_WIND_FILTER:
	case RT5640_DRC_AGC_1:
	case RT5640_DRC_AGC_2:
	case RT5640_DRC_AGC_3:
	case RT5640_SVOL_ZC:
	case RT5640_ANC_CTRL1:
	case RT5640_ANC_CTRL2:
	case RT5640_ANC_CTRL3:
	case RT5640_JD_CTRL:
	case RT5640_ANC_JD:
	case RT5640_IRQ_CTRL1:
	case RT5640_IRQ_CTRL2:
	case RT5640_INT_IRQ_ST:
	case RT5640_GPIO_CTRL1:
	case RT5640_GPIO_CTRL2:
	case RT5640_GPIO_CTRL3:
	case RT5640_DSP_CTRL1:
	case RT5640_DSP_CTRL2:
	case RT5640_DSP_CTRL3:
	case RT5640_DSP_CTRL4:
	case RT5640_PGM_REG_ARR1:
	case RT5640_PGM_REG_ARR2:
	case RT5640_PGM_REG_ARR3:
	case RT5640_PGM_REG_ARR4:
	case RT5640_PGM_REG_ARR5:
	case RT5640_SCB_FUNC:
	case RT5640_SCB_CTRL:
	case RT5640_BASE_BACK:
	case RT5640_MP3_PLUS1:
	case RT5640_MP3_PLUS2:
	case RT5640_3D_HP:
	case RT5640_ADJ_HPF:
	case RT5640_HP_CALIB_AMP_DET:
	case RT5640_HP_CALIB2:
	case RT5640_SV_ZCD1:
	case RT5640_SV_ZCD2:
	case RT5640_DUMMY1:
	case RT5640_DUMMY2:
	case RT5640_DUMMY3:
	case RT5640_VENDOR_ID:
	case RT5640_VENDOR_ID1:
	case RT5640_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}