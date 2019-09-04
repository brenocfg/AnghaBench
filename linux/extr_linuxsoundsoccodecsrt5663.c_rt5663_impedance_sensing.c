#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {unsigned int impedance_sensing_num; } ;
struct rt5663_priv {scalar_t__ jack_type; TYPE_2__* imp_table; TYPE_1__ pdata; } ;
struct TYPE_4__ {int vol; int dc_offset_l_manual_mic; int dc_offset_r_manual_mic; int dc_offset_l_manual; int dc_offset_r_manual; unsigned int imp_min; unsigned int imp_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5663_ADDA_CLK_1 ; 
 int /*<<< orphan*/  RT5663_ADDA_RST ; 
 int /*<<< orphan*/  RT5663_ANA_BIAS_CUR_1 ; 
 int /*<<< orphan*/  RT5663_ASRC_2 ; 
 int /*<<< orphan*/  RT5663_BYPASS_STO_DAC ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_2 ; 
 int /*<<< orphan*/  RT5663_CHOP_ADC ; 
 int /*<<< orphan*/  RT5663_DEPOP_1 ; 
 int /*<<< orphan*/  RT5663_DEPOP_2 ; 
 int RT5663_DIG_25M_CLK_DIS ; 
 int RT5663_DIG_25M_CLK_EN ; 
 int RT5663_DIG_25M_CLK_MASK ; 
 int RT5663_DRE_GAIN_HP_MASK ; 
 int /*<<< orphan*/  RT5663_DUMMY_1 ; 
 int /*<<< orphan*/  RT5663_DUMMY_2 ; 
 int /*<<< orphan*/  RT5663_GLB_CLK ; 
 int /*<<< orphan*/  RT5663_HP_BIAS ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_2 ; 
 int /*<<< orphan*/  RT5663_HP_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_HP_CHARGE_PUMP_2 ; 
 int /*<<< orphan*/  RT5663_HP_IMP_SEN_1 ; 
 int /*<<< orphan*/  RT5663_HP_IMP_SEN_4 ; 
 int /*<<< orphan*/  RT5663_HP_LOGIC_1 ; 
 int /*<<< orphan*/  RT5663_HP_LOGIC_2 ; 
 int /*<<< orphan*/  RT5663_HP_OUT_EN ; 
 int RT5663_I2S_PD1_MASK ; 
 int /*<<< orphan*/  RT5663_INT_ST_1 ; 
 int /*<<< orphan*/  RT5663_IRQ_3 ; 
 int /*<<< orphan*/  RT5663_MIC_DECRO_2 ; 
 int /*<<< orphan*/  RT5663_MIC_DECRO_3 ; 
 int /*<<< orphan*/  RT5663_MIC_DECRO_5 ; 
 int /*<<< orphan*/  RT5663_MIC_DECRO_6 ; 
 int /*<<< orphan*/  RT5663_PRE_DIV_GATING_1 ; 
 int /*<<< orphan*/  RT5663_PRE_DIV_GATING_2 ; 
 int RT5663_PWR_ADC_L1 ; 
 int RT5663_PWR_ADC_R1 ; 
 int RT5663_PWR_ADC_S1F ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_2 ; 
 int RT5663_PWR_DAC_L1 ; 
 int RT5663_PWR_DAC_R1 ; 
 int RT5663_PWR_DAC_S1F ; 
 int /*<<< orphan*/  RT5663_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5663_PWR_DIG_2 ; 
 int RT5663_PWR_FV1 ; 
 int RT5663_PWR_FV1_MASK ; 
 int RT5663_PWR_FV2 ; 
 int RT5663_PWR_FV2_MASK ; 
 int RT5663_PWR_LDO_DACREF_MASK ; 
 int RT5663_PWR_LDO_DACREF_ON ; 
 int RT5663_PWR_RECMIX1 ; 
 int RT5663_PWR_RECMIX2 ; 
 int RT5663_PWR_VREF1 ; 
 int RT5663_PWR_VREF1_MASK ; 
 int RT5663_PWR_VREF2 ; 
 int RT5663_PWR_VREF2_MASK ; 
 int /*<<< orphan*/  RT5663_RC_CLK ; 
 int /*<<< orphan*/  RT5663_RECMIX ; 
 int RT5663_SCLK_SRC_MASK ; 
 int RT5663_SCLK_SRC_RCCLK ; 
 int /*<<< orphan*/  RT5663_STO1_ADC_MIXER ; 
 int /*<<< orphan*/  RT5663_STO1_HPF_ADJ1 ; 
 int /*<<< orphan*/  RT5663_STO_DAC_MIXER ; 
 int /*<<< orphan*/  RT5663_STO_DRE_1 ; 
 int /*<<< orphan*/  RT5663_STO_DRE_10 ; 
 int /*<<< orphan*/  RT5663_STO_DRE_9 ; 
 scalar_t__ SND_JACK_HEADSET ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5663_impedance_sensing(struct snd_soc_component *component)
{
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);
	unsigned int value, i, reg84, reg26, reg2fa, reg91, reg10, reg80;

	for (i = 0; i < rt5663->pdata.impedance_sensing_num; i++) {
		if (rt5663->imp_table[i].vol == 7)
			break;
	}

	if (rt5663->jack_type == SND_JACK_HEADSET) {
		snd_soc_component_write(component, RT5663_MIC_DECRO_2,
			rt5663->imp_table[i].dc_offset_l_manual_mic >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_3,
			rt5663->imp_table[i].dc_offset_l_manual_mic & 0xffff);
		snd_soc_component_write(component, RT5663_MIC_DECRO_5,
			rt5663->imp_table[i].dc_offset_r_manual_mic >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_6,
			rt5663->imp_table[i].dc_offset_r_manual_mic & 0xffff);
	} else {
		snd_soc_component_write(component, RT5663_MIC_DECRO_2,
			rt5663->imp_table[i].dc_offset_l_manual >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_3,
			rt5663->imp_table[i].dc_offset_l_manual & 0xffff);
		snd_soc_component_write(component, RT5663_MIC_DECRO_5,
			rt5663->imp_table[i].dc_offset_r_manual >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_6,
			rt5663->imp_table[i].dc_offset_r_manual & 0xffff);
	}

	reg84 = snd_soc_component_read32(component, RT5663_ASRC_2);
	reg26 = snd_soc_component_read32(component, RT5663_STO1_ADC_MIXER);
	reg2fa = snd_soc_component_read32(component, RT5663_DUMMY_1);
	reg91 = snd_soc_component_read32(component, RT5663_HP_CHARGE_PUMP_1);
	reg10 = snd_soc_component_read32(component, RT5663_RECMIX);
	reg80 = snd_soc_component_read32(component, RT5663_GLB_CLK);

	snd_soc_component_update_bits(component, RT5663_STO_DRE_1, 0x8000, 0);
	snd_soc_component_write(component, RT5663_ASRC_2, 0);
	snd_soc_component_write(component, RT5663_STO1_ADC_MIXER, 0x4040);
	snd_soc_component_update_bits(component, RT5663_PWR_ANLG_1,
		RT5663_PWR_VREF1_MASK | RT5663_PWR_VREF2_MASK |
		RT5663_PWR_FV1_MASK | RT5663_PWR_FV2_MASK,
		RT5663_PWR_VREF1 | RT5663_PWR_VREF2);
	usleep_range(10000, 10005);
	snd_soc_component_update_bits(component, RT5663_PWR_ANLG_1,
		RT5663_PWR_FV1_MASK | RT5663_PWR_FV2_MASK,
		RT5663_PWR_FV1 | RT5663_PWR_FV2);
	snd_soc_component_update_bits(component, RT5663_GLB_CLK, RT5663_SCLK_SRC_MASK,
		RT5663_SCLK_SRC_RCCLK);
	snd_soc_component_update_bits(component, RT5663_RC_CLK, RT5663_DIG_25M_CLK_MASK,
		RT5663_DIG_25M_CLK_EN);
	snd_soc_component_update_bits(component, RT5663_ADDA_CLK_1, RT5663_I2S_PD1_MASK, 0);
	snd_soc_component_write(component, RT5663_PRE_DIV_GATING_1, 0xff00);
	snd_soc_component_write(component, RT5663_PRE_DIV_GATING_2, 0xfffc);
	snd_soc_component_write(component, RT5663_HP_CHARGE_PUMP_1, 0x1232);
	snd_soc_component_write(component, RT5663_HP_LOGIC_2, 0x0005);
	snd_soc_component_write(component, RT5663_DEPOP_2, 0x3003);
	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0030, 0x0030);
	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0003, 0x0003);
	snd_soc_component_update_bits(component, RT5663_PWR_DIG_2,
		RT5663_PWR_ADC_S1F | RT5663_PWR_DAC_S1F,
		RT5663_PWR_ADC_S1F | RT5663_PWR_DAC_S1F);
	snd_soc_component_update_bits(component, RT5663_PWR_DIG_1,
		RT5663_PWR_DAC_L1 | RT5663_PWR_DAC_R1 |
		RT5663_PWR_LDO_DACREF_MASK | RT5663_PWR_ADC_L1 |
		RT5663_PWR_ADC_R1,
		RT5663_PWR_DAC_L1 | RT5663_PWR_DAC_R1 |
		RT5663_PWR_LDO_DACREF_ON | RT5663_PWR_ADC_L1 |
		RT5663_PWR_ADC_R1);
	msleep(40);
	snd_soc_component_update_bits(component, RT5663_PWR_ANLG_2,
		RT5663_PWR_RECMIX1 | RT5663_PWR_RECMIX2,
		RT5663_PWR_RECMIX1 | RT5663_PWR_RECMIX2);
	msleep(30);
	snd_soc_component_write(component, RT5663_HP_CHARGE_PUMP_2, 0x1371);
	snd_soc_component_write(component, RT5663_STO_DAC_MIXER, 0);
	snd_soc_component_write(component, RT5663_BYPASS_STO_DAC, 0x000c);
	snd_soc_component_write(component, RT5663_HP_BIAS, 0xafaa);
	snd_soc_component_write(component, RT5663_CHARGE_PUMP_1, 0x2224);
	snd_soc_component_write(component, RT5663_HP_OUT_EN, 0x8088);
	snd_soc_component_write(component, RT5663_CHOP_ADC, 0x3000);
	snd_soc_component_write(component, RT5663_ADDA_RST, 0xc000);
	snd_soc_component_write(component, RT5663_STO1_HPF_ADJ1, 0x3320);
	snd_soc_component_write(component, RT5663_HP_CALIB_2, 0x00c9);
	snd_soc_component_write(component, RT5663_DUMMY_1, 0x004c);
	snd_soc_component_write(component, RT5663_ANA_BIAS_CUR_1, 0x7733);
	snd_soc_component_write(component, RT5663_CHARGE_PUMP_2, 0x7777);
	snd_soc_component_write(component, RT5663_STO_DRE_9, 0x0007);
	snd_soc_component_write(component, RT5663_STO_DRE_10, 0x0007);
	snd_soc_component_write(component, RT5663_DUMMY_2, 0x02a4);
	snd_soc_component_write(component, RT5663_RECMIX, 0x0005);
	snd_soc_component_write(component, RT5663_HP_IMP_SEN_1, 0x4334);
	snd_soc_component_update_bits(component, RT5663_IRQ_3, 0x0004, 0x0004);
	snd_soc_component_write(component, RT5663_HP_LOGIC_1, 0x2200);
	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x3000, 0x3000);
	snd_soc_component_write(component, RT5663_HP_LOGIC_1, 0x6200);

	for (i = 0; i < 100; i++) {
		msleep(20);
		if (snd_soc_component_read32(component, RT5663_INT_ST_1) & 0x2)
			break;
	}

	value = snd_soc_component_read32(component, RT5663_HP_IMP_SEN_4);

	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x3000, 0);
	snd_soc_component_write(component, RT5663_INT_ST_1, 0);
	snd_soc_component_write(component, RT5663_HP_LOGIC_1, 0);
	snd_soc_component_update_bits(component, RT5663_RC_CLK, RT5663_DIG_25M_CLK_MASK,
		RT5663_DIG_25M_CLK_DIS);
	snd_soc_component_write(component, RT5663_GLB_CLK, reg80);
	snd_soc_component_write(component, RT5663_RECMIX, reg10);
	snd_soc_component_write(component, RT5663_DUMMY_2, 0x00a4);
	snd_soc_component_write(component, RT5663_DUMMY_1, reg2fa);
	snd_soc_component_write(component, RT5663_HP_CALIB_2, 0x00c8);
	snd_soc_component_write(component, RT5663_STO1_HPF_ADJ1, 0xb320);
	snd_soc_component_write(component, RT5663_ADDA_RST, 0xe400);
	snd_soc_component_write(component, RT5663_CHOP_ADC, 0x2000);
	snd_soc_component_write(component, RT5663_HP_OUT_EN, 0x0008);
	snd_soc_component_update_bits(component, RT5663_PWR_ANLG_2,
		RT5663_PWR_RECMIX1 | RT5663_PWR_RECMIX2, 0);
	snd_soc_component_update_bits(component, RT5663_PWR_DIG_1,
		RT5663_PWR_DAC_L1 | RT5663_PWR_DAC_R1 |
		RT5663_PWR_LDO_DACREF_MASK | RT5663_PWR_ADC_L1 |
		RT5663_PWR_ADC_R1, 0);
	snd_soc_component_update_bits(component, RT5663_PWR_DIG_2,
		RT5663_PWR_ADC_S1F | RT5663_PWR_DAC_S1F, 0);
	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0003, 0);
	snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0030, 0);
	snd_soc_component_write(component, RT5663_HP_LOGIC_2, 0);
	snd_soc_component_write(component, RT5663_HP_CHARGE_PUMP_1, reg91);
	snd_soc_component_update_bits(component, RT5663_PWR_ANLG_1,
		RT5663_PWR_VREF1_MASK | RT5663_PWR_VREF2_MASK, 0);
	snd_soc_component_write(component, RT5663_STO1_ADC_MIXER, reg26);
	snd_soc_component_write(component, RT5663_ASRC_2, reg84);

	for (i = 0; i < rt5663->pdata.impedance_sensing_num; i++) {
		if (value >= rt5663->imp_table[i].imp_min &&
			value <= rt5663->imp_table[i].imp_max)
			break;
	}

	snd_soc_component_update_bits(component, RT5663_STO_DRE_9, RT5663_DRE_GAIN_HP_MASK,
		rt5663->imp_table[i].vol);
	snd_soc_component_update_bits(component, RT5663_STO_DRE_10, RT5663_DRE_GAIN_HP_MASK,
		rt5663->imp_table[i].vol);

	if (rt5663->jack_type == SND_JACK_HEADSET) {
		snd_soc_component_write(component, RT5663_MIC_DECRO_2,
			rt5663->imp_table[i].dc_offset_l_manual_mic >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_3,
			rt5663->imp_table[i].dc_offset_l_manual_mic & 0xffff);
		snd_soc_component_write(component, RT5663_MIC_DECRO_5,
			rt5663->imp_table[i].dc_offset_r_manual_mic >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_6,
			rt5663->imp_table[i].dc_offset_r_manual_mic & 0xffff);
	} else {
		snd_soc_component_write(component, RT5663_MIC_DECRO_2,
			rt5663->imp_table[i].dc_offset_l_manual >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_3,
			rt5663->imp_table[i].dc_offset_l_manual & 0xffff);
		snd_soc_component_write(component, RT5663_MIC_DECRO_5,
			rt5663->imp_table[i].dc_offset_r_manual >> 16);
		snd_soc_component_write(component, RT5663_MIC_DECRO_6,
			rt5663->imp_table[i].dc_offset_r_manual & 0xffff);
	}

	return 0;
}