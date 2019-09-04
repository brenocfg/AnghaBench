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
struct rt5665_priv {int calibration_done; int /*<<< orphan*/  calibrate_mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5665_ADDA_CLK_1 ; 
 int /*<<< orphan*/  RT5665_ASRC_8 ; 
 int /*<<< orphan*/  RT5665_BIAS_CUR_CTRL_8 ; 
 int /*<<< orphan*/  RT5665_CALIB_ADC_CTRL ; 
 int /*<<< orphan*/  RT5665_CHOP_DAC ; 
 int /*<<< orphan*/  RT5665_DIG_MISC ; 
 int /*<<< orphan*/  RT5665_EJD_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_GLB_CLK ; 
 int /*<<< orphan*/  RT5665_HP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_HP_CALIB_CTRL_2 ; 
 int /*<<< orphan*/  RT5665_HP_CALIB_STA_1 ; 
 int /*<<< orphan*/  RT5665_HP_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5665_HP_LOGIC_CTRL_2 ; 
 int /*<<< orphan*/  RT5665_MICBIAS_2 ; 
 int /*<<< orphan*/  RT5665_MONOMIX_IN_GAIN ; 
 int /*<<< orphan*/  RT5665_MONO_AMP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_MONO_AMP_CALIB_STA1 ; 
 int /*<<< orphan*/  RT5665_MONO_OUT ; 
 int /*<<< orphan*/  RT5665_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5665_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5665_PWR_MIXER ; 
 int /*<<< orphan*/  RT5665_RESET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt5665_calibrate(struct rt5665_priv *rt5665)
{
	int value, count;

	mutex_lock(&rt5665->calibrate_mutex);

	regcache_cache_bypass(rt5665->regmap, true);

	regmap_write(rt5665->regmap, RT5665_RESET, 0);
	regmap_write(rt5665->regmap, RT5665_BIAS_CUR_CTRL_8, 0xa602);
	regmap_write(rt5665->regmap, RT5665_HP_CHARGE_PUMP_1, 0x0c26);
	regmap_write(rt5665->regmap, RT5665_MONOMIX_IN_GAIN, 0x021f);
	regmap_write(rt5665->regmap, RT5665_MONO_OUT, 0x480a);
	regmap_write(rt5665->regmap, RT5665_PWR_MIXER, 0x083f);
	regmap_write(rt5665->regmap, RT5665_PWR_DIG_1, 0x0180);
	regmap_write(rt5665->regmap, RT5665_EJD_CTRL_1, 0x4040);
	regmap_write(rt5665->regmap, RT5665_HP_LOGIC_CTRL_2, 0x0000);
	regmap_write(rt5665->regmap, RT5665_DIG_MISC, 0x0001);
	regmap_write(rt5665->regmap, RT5665_MICBIAS_2, 0x0380);
	regmap_write(rt5665->regmap, RT5665_GLB_CLK, 0x8000);
	regmap_write(rt5665->regmap, RT5665_ADDA_CLK_1, 0x1000);
	regmap_write(rt5665->regmap, RT5665_CHOP_DAC, 0x3030);
	regmap_write(rt5665->regmap, RT5665_CALIB_ADC_CTRL, 0x3c05);
	regmap_write(rt5665->regmap, RT5665_PWR_ANLG_1, 0xaa3e);
	usleep_range(15000, 20000);
	regmap_write(rt5665->regmap, RT5665_PWR_ANLG_1, 0xfe7e);
	regmap_write(rt5665->regmap, RT5665_HP_CALIB_CTRL_2, 0x0321);

	regmap_write(rt5665->regmap, RT5665_HP_CALIB_CTRL_1, 0xfc00);
	count = 0;
	while (true) {
		regmap_read(rt5665->regmap, RT5665_HP_CALIB_STA_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 60) {
			pr_err("HP Calibration Failure\n");
			regmap_write(rt5665->regmap, RT5665_RESET, 0);
			regcache_cache_bypass(rt5665->regmap, false);
			goto out_unlock;
		}

		count++;
	}

	regmap_write(rt5665->regmap, RT5665_MONO_AMP_CALIB_CTRL_1, 0x9e24);
	count = 0;
	while (true) {
		regmap_read(rt5665->regmap, RT5665_MONO_AMP_CALIB_STA1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 60) {
			pr_err("MONO Calibration Failure\n");
			regmap_write(rt5665->regmap, RT5665_RESET, 0);
			regcache_cache_bypass(rt5665->regmap, false);
			goto out_unlock;
		}

		count++;
	}

	regmap_write(rt5665->regmap, RT5665_RESET, 0);
	regcache_cache_bypass(rt5665->regmap, false);

	regcache_mark_dirty(rt5665->regmap);
	regcache_sync(rt5665->regmap);

	regmap_write(rt5665->regmap, RT5665_BIAS_CUR_CTRL_8, 0xa602);
	regmap_write(rt5665->regmap, RT5665_ASRC_8, 0x0120);

out_unlock:
	rt5665->calibration_done = true;
	mutex_unlock(&rt5665->calibrate_mutex);
}