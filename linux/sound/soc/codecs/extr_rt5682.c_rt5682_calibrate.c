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
struct rt5682_priv {int /*<<< orphan*/  calibrate_mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5682_A_DAC1_MUX ; 
 int /*<<< orphan*/  RT5682_CALIB_ADC_CTRL ; 
 int /*<<< orphan*/  RT5682_CAL_REC ; 
 int /*<<< orphan*/  RT5682_CHOP_DAC ; 
 int /*<<< orphan*/  RT5682_GLB_CLK ; 
 int /*<<< orphan*/  RT5682_HP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5682_HP_CALIB_CTRL_2 ; 
 int /*<<< orphan*/  RT5682_HP_CALIB_CTRL_3 ; 
 int /*<<< orphan*/  RT5682_HP_CALIB_STA_1 ; 
 int /*<<< orphan*/  RT5682_HP_IMP_SENS_CTRL_19 ; 
 int /*<<< orphan*/  RT5682_HP_LOGIC_CTRL_2 ; 
 int /*<<< orphan*/  RT5682_MICBIAS_2 ; 
 int /*<<< orphan*/  RT5682_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5682_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5682_STO1_ADC_MIXER ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5682_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt5682_calibrate(struct rt5682_priv *rt5682)
{
	int value, count;

	mutex_lock(&rt5682->calibrate_mutex);

	rt5682_reset(rt5682->regmap);
	regmap_write(rt5682->regmap, RT5682_PWR_ANLG_1, 0xa2af);
	usleep_range(15000, 20000);
	regmap_write(rt5682->regmap, RT5682_PWR_ANLG_1, 0xf2af);
	regmap_write(rt5682->regmap, RT5682_MICBIAS_2, 0x0300);
	regmap_write(rt5682->regmap, RT5682_GLB_CLK, 0x8000);
	regmap_write(rt5682->regmap, RT5682_PWR_DIG_1, 0x0100);
	regmap_write(rt5682->regmap, RT5682_HP_IMP_SENS_CTRL_19, 0x3800);
	regmap_write(rt5682->regmap, RT5682_CHOP_DAC, 0x3000);
	regmap_write(rt5682->regmap, RT5682_CALIB_ADC_CTRL, 0x7005);
	regmap_write(rt5682->regmap, RT5682_STO1_ADC_MIXER, 0x686c);
	regmap_write(rt5682->regmap, RT5682_CAL_REC, 0x0d0d);
	regmap_write(rt5682->regmap, RT5682_HP_CALIB_CTRL_2, 0x0321);
	regmap_write(rt5682->regmap, RT5682_HP_LOGIC_CTRL_2, 0x0004);
	regmap_write(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0x7c00);
	regmap_write(rt5682->regmap, RT5682_HP_CALIB_CTRL_3, 0x06a1);
	regmap_write(rt5682->regmap, RT5682_A_DAC1_MUX, 0x0311);
	regmap_write(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0x7c00);

	regmap_write(rt5682->regmap, RT5682_HP_CALIB_CTRL_1, 0xfc00);

	for (count = 0; count < 60; count++) {
		regmap_read(rt5682->regmap, RT5682_HP_CALIB_STA_1, &value);
		if (!(value & 0x8000))
			break;

		usleep_range(10000, 10005);
	}

	if (count >= 60)
		pr_err("HP Calibration Failure\n");

	/* restore settings */
	regmap_write(rt5682->regmap, RT5682_PWR_ANLG_1, 0x02af);
	regmap_write(rt5682->regmap, RT5682_MICBIAS_2, 0x0080);
	regmap_write(rt5682->regmap, RT5682_GLB_CLK, 0x0000);
	regmap_write(rt5682->regmap, RT5682_PWR_DIG_1, 0x0000);
	regmap_write(rt5682->regmap, RT5682_CHOP_DAC, 0x2000);
	regmap_write(rt5682->regmap, RT5682_CALIB_ADC_CTRL, 0x2005);
	regmap_write(rt5682->regmap, RT5682_STO1_ADC_MIXER, 0xc0c4);

	mutex_unlock(&rt5682->calibrate_mutex);

}