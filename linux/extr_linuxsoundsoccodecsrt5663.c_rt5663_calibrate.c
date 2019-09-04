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
struct rt5663_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5663_ADDA_CLK_1 ; 
 int /*<<< orphan*/  RT5663_ADDA_RST ; 
 int /*<<< orphan*/  RT5663_ANA_BIAS_CUR_1 ; 
 int /*<<< orphan*/  RT5663_ANA_BIAS_CUR_4 ; 
 int /*<<< orphan*/  RT5663_BIAS_CUR_8 ; 
 int /*<<< orphan*/  RT5663_BYPASS_STO_DAC ; 
 int /*<<< orphan*/  RT5663_CBJ_1 ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_2 ; 
 int /*<<< orphan*/  RT5663_CHOP_ADC ; 
 int /*<<< orphan*/  RT5663_DACREF_LDO ; 
 int /*<<< orphan*/  RT5663_DEPOP_1 ; 
 int /*<<< orphan*/  RT5663_DEPOP_2 ; 
 int /*<<< orphan*/  RT5663_DIG_MISC ; 
 int /*<<< orphan*/  RT5663_DUMMY_1 ; 
 int /*<<< orphan*/  RT5663_DUMMY_2 ; 
 int /*<<< orphan*/  RT5663_EM_JACK_TYPE_1 ; 
 int /*<<< orphan*/  RT5663_EM_JACK_TYPE_2 ; 
 int /*<<< orphan*/  RT5663_GLB_CLK ; 
 int /*<<< orphan*/  RT5663_HP_BIAS ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_1 ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_1_1 ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_2 ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_3 ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_7 ; 
 int /*<<< orphan*/  RT5663_HP_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_HP_IMP_SEN_19 ; 
 int /*<<< orphan*/  RT5663_HP_OUT_EN ; 
 int /*<<< orphan*/  RT5663_IL_CMD_2 ; 
 int /*<<< orphan*/  RT5663_INT_ST_2 ; 
 int /*<<< orphan*/  RT5663_PRE_DIV_GATING_1 ; 
 int /*<<< orphan*/  RT5663_PRE_DIV_GATING_2 ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_2 ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_3 ; 
 int /*<<< orphan*/  RT5663_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5663_PWR_DIG_2 ; 
 int /*<<< orphan*/  RT5663_RC_CLK ; 
 int /*<<< orphan*/  RT5663_RECMIX ; 
 int /*<<< orphan*/  RT5663_RESET ; 
 int /*<<< orphan*/  RT5663_STO1_ADC_MIXER ; 
 int /*<<< orphan*/  RT5663_STO1_HPF_ADJ1 ; 
 int /*<<< orphan*/  RT5663_STO_DAC_MIXER ; 
 int /*<<< orphan*/  RT5663_STO_DRE_10 ; 
 int /*<<< orphan*/  RT5663_STO_DRE_9 ; 
 int /*<<< orphan*/  RT5663_VREFADJ_OP ; 
 int /*<<< orphan*/  RT5663_VREF_RECMIX ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt5663_calibrate(struct rt5663_priv *rt5663)
{
	int value, count;

	regmap_write(rt5663->regmap, RT5663_RESET, 0x0000);
	msleep(20);
	regmap_write(rt5663->regmap, RT5663_ANA_BIAS_CUR_4, 0x00a1);
	regmap_write(rt5663->regmap, RT5663_RC_CLK, 0x0380);
	regmap_write(rt5663->regmap, RT5663_GLB_CLK, 0x8000);
	regmap_write(rt5663->regmap, RT5663_ADDA_CLK_1, 0x1000);
	regmap_write(rt5663->regmap, RT5663_VREF_RECMIX, 0x0032);
	regmap_write(rt5663->regmap, RT5663_HP_IMP_SEN_19, 0x000c);
	regmap_write(rt5663->regmap, RT5663_DUMMY_1, 0x0324);
	regmap_write(rt5663->regmap, RT5663_DIG_MISC, 0x8001);
	regmap_write(rt5663->regmap, RT5663_VREFADJ_OP, 0x0f28);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_1, 0xa23b);
	msleep(30);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_1, 0xf23b);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_2, 0x8000);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_3, 0x0008);
	regmap_write(rt5663->regmap, RT5663_PRE_DIV_GATING_1, 0xffff);
	regmap_write(rt5663->regmap, RT5663_PRE_DIV_GATING_2, 0xffff);
	regmap_write(rt5663->regmap, RT5663_CBJ_1, 0x8c10);
	regmap_write(rt5663->regmap, RT5663_IL_CMD_2, 0x00c1);
	regmap_write(rt5663->regmap, RT5663_EM_JACK_TYPE_1, 0xb880);
	regmap_write(rt5663->regmap, RT5663_EM_JACK_TYPE_2, 0x4110);
	regmap_write(rt5663->regmap, RT5663_EM_JACK_TYPE_2, 0x4118);

	count = 0;
	while (true) {
		regmap_read(rt5663->regmap, RT5663_INT_ST_2, &value);
		if (!(value & 0x80))
			usleep_range(10000, 10005);
		else
			break;

		if (++count > 200)
			break;
	}

	regmap_write(rt5663->regmap, RT5663_HP_IMP_SEN_19, 0x0000);
	regmap_write(rt5663->regmap, RT5663_DEPOP_2, 0x3003);
	regmap_write(rt5663->regmap, RT5663_DEPOP_1, 0x0038);
	regmap_write(rt5663->regmap, RT5663_DEPOP_1, 0x003b);
	regmap_write(rt5663->regmap, RT5663_PWR_DIG_2, 0x8400);
	regmap_write(rt5663->regmap, RT5663_PWR_DIG_1, 0x8df8);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_2, 0x8003);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_3, 0x018c);
	regmap_write(rt5663->regmap, RT5663_HP_CHARGE_PUMP_1, 0x1e32);
	regmap_write(rt5663->regmap, RT5663_DUMMY_2, 0x8089);
	regmap_write(rt5663->regmap, RT5663_DACREF_LDO, 0x3b0b);
	msleep(40);
	regmap_write(rt5663->regmap, RT5663_STO_DAC_MIXER, 0x0000);
	regmap_write(rt5663->regmap, RT5663_BYPASS_STO_DAC, 0x000c);
	regmap_write(rt5663->regmap, RT5663_HP_BIAS, 0xafaa);
	regmap_write(rt5663->regmap, RT5663_CHARGE_PUMP_1, 0x2224);
	regmap_write(rt5663->regmap, RT5663_HP_OUT_EN, 0x8088);
	regmap_write(rt5663->regmap, RT5663_STO_DRE_9, 0x0017);
	regmap_write(rt5663->regmap, RT5663_STO_DRE_10, 0x0017);
	regmap_write(rt5663->regmap, RT5663_STO1_ADC_MIXER, 0x4040);
	regmap_write(rt5663->regmap, RT5663_CHOP_ADC, 0x3000);
	regmap_write(rt5663->regmap, RT5663_RECMIX, 0x0005);
	regmap_write(rt5663->regmap, RT5663_ADDA_RST, 0xc000);
	regmap_write(rt5663->regmap, RT5663_STO1_HPF_ADJ1, 0x3320);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_2, 0x00c9);
	regmap_write(rt5663->regmap, RT5663_DUMMY_1, 0x004c);
	regmap_write(rt5663->regmap, RT5663_ANA_BIAS_CUR_1, 0x1111);
	regmap_write(rt5663->regmap, RT5663_BIAS_CUR_8, 0x4402);
	regmap_write(rt5663->regmap, RT5663_CHARGE_PUMP_2, 0x3311);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1, 0x0069);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_3, 0x06ce);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1_1, 0x6800);
	regmap_write(rt5663->regmap, RT5663_CHARGE_PUMP_2, 0x1100);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_7, 0x0057);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1_1, 0xe800);

	count = 0;
	while (true) {
		regmap_read(rt5663->regmap, RT5663_HP_CALIB_1_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 200)
			return;
		count++;
	}

	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1_1, 0x6200);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_7, 0x0059);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1_1, 0xe200);

	count = 0;
	while (true) {
		regmap_read(rt5663->regmap, RT5663_HP_CALIB_1_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 200)
			return;
		count++;
	}

	regmap_write(rt5663->regmap, RT5663_EM_JACK_TYPE_1, 0xb8e0);
	usleep_range(10000, 10005);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_1, 0x003b);
	usleep_range(10000, 10005);
	regmap_write(rt5663->regmap, RT5663_PWR_DIG_1, 0x0000);
	usleep_range(10000, 10005);
	regmap_write(rt5663->regmap, RT5663_DEPOP_1, 0x000b);
	usleep_range(10000, 10005);
	regmap_write(rt5663->regmap, RT5663_DEPOP_1, 0x0008);
	usleep_range(10000, 10005);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_2, 0x0000);
	usleep_range(10000, 10005);
}