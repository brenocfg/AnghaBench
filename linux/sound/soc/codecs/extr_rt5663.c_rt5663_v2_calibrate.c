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
 int /*<<< orphan*/  RT5663_BIAS_CUR_8 ; 
 int /*<<< orphan*/  RT5663_CALIB_ADC ; 
 int /*<<< orphan*/  RT5663_CHOP_DAC_L ; 
 int /*<<< orphan*/  RT5663_DIG_MISC ; 
 int /*<<< orphan*/  RT5663_GLB_CLK ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_1 ; 
 int /*<<< orphan*/  RT5663_HP_CALIB_2 ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5663_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5663_RC_CLK ; 
 int /*<<< orphan*/  RT5663_RECMIX ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt5663_v2_calibrate(struct rt5663_priv *rt5663)
{
	regmap_write(rt5663->regmap, RT5663_BIAS_CUR_8, 0xa402);
	regmap_write(rt5663->regmap, RT5663_PWR_DIG_1, 0x0100);
	regmap_write(rt5663->regmap, RT5663_RECMIX, 0x4040);
	regmap_write(rt5663->regmap, RT5663_DIG_MISC, 0x0001);
	regmap_write(rt5663->regmap, RT5663_RC_CLK, 0x0380);
	regmap_write(rt5663->regmap, RT5663_GLB_CLK, 0x8000);
	regmap_write(rt5663->regmap, RT5663_ADDA_CLK_1, 0x1000);
	regmap_write(rt5663->regmap, RT5663_CHOP_DAC_L, 0x3030);
	regmap_write(rt5663->regmap, RT5663_CALIB_ADC, 0x3c05);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_1, 0xa23e);
	msleep(40);
	regmap_write(rt5663->regmap, RT5663_PWR_ANLG_1, 0xf23e);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_2, 0x0321);
	regmap_write(rt5663->regmap, RT5663_HP_CALIB_1, 0xfc00);
	msleep(500);
}