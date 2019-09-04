#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rt5659_priv {int /*<<< orphan*/  regmap; TYPE_1__* component; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5659_A_DAC_MUX ; 
 int /*<<< orphan*/  RT5659_BIAS_CUR_CTRL_8 ; 
 int /*<<< orphan*/  RT5659_CALIB_ADC_CTRL ; 
 int /*<<< orphan*/  RT5659_CAL_REC ; 
 int /*<<< orphan*/  RT5659_CHOP_DAC ; 
 int /*<<< orphan*/  RT5659_CLASSD_0 ; 
 int /*<<< orphan*/  RT5659_CLASSD_1 ; 
 int /*<<< orphan*/  RT5659_CLASSD_2 ; 
 int /*<<< orphan*/  RT5659_CLASSD_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_DEPOP_1 ; 
 int /*<<< orphan*/  RT5659_DIG_MISC ; 
 int /*<<< orphan*/  RT5659_GLB_CLK ; 
 int /*<<< orphan*/  RT5659_HP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_HP_CALIB_CTRL_2 ; 
 int /*<<< orphan*/  RT5659_HP_CALIB_CTRL_7 ; 
 int /*<<< orphan*/  RT5659_HP_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5659_HP_VOL ; 
 int /*<<< orphan*/  RT5659_MICBIAS_2 ; 
 int /*<<< orphan*/  RT5659_MONOMIX_IN_GAIN ; 
 int /*<<< orphan*/  RT5659_MONO_AMP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_MONO_GAIN ; 
 int /*<<< orphan*/  RT5659_MONO_NG2_CTRL_5 ; 
 int /*<<< orphan*/  RT5659_MONO_OUT ; 
 int /*<<< orphan*/  RT5659_PRE_DIV_1 ; 
 int /*<<< orphan*/  RT5659_PRE_DIV_2 ; 
 int /*<<< orphan*/  RT5659_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5659_PWR_ANLG_3 ; 
 int /*<<< orphan*/  RT5659_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5659_PWR_DIG_2 ; 
 int /*<<< orphan*/  RT5659_PWR_MIXER ; 
 int /*<<< orphan*/  RT5659_PWR_VOL ; 
 int /*<<< orphan*/  RT5659_SPK_DC_CAILB_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_SPK_DC_CAILB_CTRL_3 ; 
 int /*<<< orphan*/  RT5659_SPK_L_MIXER ; 
 int /*<<< orphan*/  RT5659_SPK_R_MIXER ; 
 int /*<<< orphan*/  RT5659_SPO_AMP_GAIN ; 
 int /*<<< orphan*/  RT5659_SPO_VOL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt5659_calibrate(struct rt5659_priv *rt5659)
{
	int value, count;

	/* Calibrate HPO Start */
	/* Fine tune HP Performance */
	regmap_write(rt5659->regmap, RT5659_BIAS_CUR_CTRL_8, 0xa502);
	regmap_write(rt5659->regmap, RT5659_CHOP_DAC, 0x3030);

	regmap_write(rt5659->regmap, RT5659_PRE_DIV_1, 0xef00);
	regmap_write(rt5659->regmap, RT5659_PRE_DIV_2, 0xeffc);
	regmap_write(rt5659->regmap, RT5659_MICBIAS_2, 0x0280);
	regmap_write(rt5659->regmap, RT5659_DIG_MISC, 0x0001);
	regmap_write(rt5659->regmap, RT5659_GLB_CLK, 0x8000);

	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_1, 0xaa7e);
	msleep(60);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_1, 0xfe7e);
	msleep(50);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0004);
	regmap_write(rt5659->regmap, RT5659_PWR_DIG_2, 0x0400);
	msleep(50);
	regmap_write(rt5659->regmap, RT5659_PWR_DIG_1, 0x0080);
	usleep_range(10000, 10005);
	regmap_write(rt5659->regmap, RT5659_DEPOP_1, 0x0009);
	msleep(50);
	regmap_write(rt5659->regmap, RT5659_PWR_DIG_1, 0x0f80);
	msleep(50);
	regmap_write(rt5659->regmap, RT5659_HP_CHARGE_PUMP_1, 0x0e16);
	msleep(50);

	/* Enalbe K ADC Power And Clock */
	regmap_write(rt5659->regmap, RT5659_CAL_REC, 0x0505);
	msleep(50);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0184);
	regmap_write(rt5659->regmap, RT5659_CALIB_ADC_CTRL, 0x3c05);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c1);

	/* K Headphone */
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x5100);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0014);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0xd100);
	msleep(60);

	/* Manual K ADC Offset */
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x4900);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0016);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	while (true) {
		regmap_read(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 30) {
			dev_err(rt5659->component->dev,
				"HP Calibration 1 Failure\n");
			return;
		}

		count++;
	}

	/* Manual K Internal Path Offset */
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x2cc1);
	regmap_write(rt5659->regmap, RT5659_HP_VOL, 0x0000);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, 0x4500);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x001f);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	while (true) {
		regmap_read(rt5659->regmap, RT5659_HP_CALIB_CTRL_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 85) {
			dev_err(rt5659->component->dev,
				"HP Calibration 2 Failure\n");
			return;
		}

		count++;
	}

	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_7, 0x0000);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c0);
	/* Calibrate HPO End */

	/* Calibrate SPO Start */
	regmap_write(rt5659->regmap, RT5659_CLASSD_0, 0x2021);
	regmap_write(rt5659->regmap, RT5659_CLASSD_CTRL_1, 0x0260);
	regmap_write(rt5659->regmap, RT5659_PWR_MIXER, 0x3000);
	regmap_write(rt5659->regmap, RT5659_PWR_VOL, 0xc000);
	regmap_write(rt5659->regmap, RT5659_A_DAC_MUX, 0x000c);
	regmap_write(rt5659->regmap, RT5659_DIG_MISC, 0x8000);
	regmap_write(rt5659->regmap, RT5659_SPO_VOL, 0x0808);
	regmap_write(rt5659->regmap, RT5659_SPK_L_MIXER, 0x001e);
	regmap_write(rt5659->regmap, RT5659_SPK_R_MIXER, 0x001e);
	regmap_write(rt5659->regmap, RT5659_CLASSD_1, 0x0803);
	regmap_write(rt5659->regmap, RT5659_CLASSD_2, 0x0554);
	regmap_write(rt5659->regmap, RT5659_SPO_AMP_GAIN, 0x1103);

	/* Enalbe K ADC Power And Clock */
	regmap_write(rt5659->regmap, RT5659_CAL_REC, 0x0909);
	regmap_update_bits(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x0001,
		0x0001);

	/* Start Calibration */
	regmap_write(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x0000);
	regmap_write(rt5659->regmap, RT5659_CLASSD_0, 0x0021);
	regmap_write(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_1, 0x3e80);
	regmap_update_bits(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	while (true) {
		regmap_read(rt5659->regmap,
				RT5659_SPK_DC_CAILB_CTRL_1, &value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 10) {
			dev_err(rt5659->component->dev,
				"SPK Calibration Failure\n");
			return;
		}

		count++;
	}
	/* Calibrate SPO End */

	/* Calibrate MONO Start */
	regmap_write(rt5659->regmap, RT5659_DIG_MISC, 0x0000);
	regmap_write(rt5659->regmap, RT5659_MONOMIX_IN_GAIN, 0x021f);
	regmap_write(rt5659->regmap, RT5659_MONO_OUT, 0x480a);
	/* MONO NG2 GAIN 5dB */
	regmap_write(rt5659->regmap, RT5659_MONO_GAIN, 0x0003);
	regmap_write(rt5659->regmap, RT5659_MONO_NG2_CTRL_5, 0x0009);

	/* Start Calibration */
	regmap_write(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x000f);
	regmap_write(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e00);
	regmap_update_bits(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1,
		0x8000, 0x8000);

	count = 0;
	while (true) {
		regmap_read(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1,
			&value);
		if (value & 0x8000)
			usleep_range(10000, 10005);
		else
			break;

		if (count > 35) {
			dev_err(rt5659->component->dev,
				"Mono Calibration Failure\n");
			return;
		}

		count++;
	}

	regmap_write(rt5659->regmap, RT5659_SPK_DC_CAILB_CTRL_3, 0x0003);
	/* Calibrate MONO End */

	/* Power Off */
	regmap_write(rt5659->regmap, RT5659_CAL_REC, 0x0808);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_3, 0x0000);
	regmap_write(rt5659->regmap, RT5659_CALIB_ADC_CTRL, 0x2005);
	regmap_write(rt5659->regmap, RT5659_HP_CALIB_CTRL_2, 0x20c0);
	regmap_write(rt5659->regmap, RT5659_DEPOP_1, 0x0000);
	regmap_write(rt5659->regmap, RT5659_CLASSD_1, 0x0011);
	regmap_write(rt5659->regmap, RT5659_CLASSD_2, 0x0150);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_1, 0xfe3e);
	regmap_write(rt5659->regmap, RT5659_MONO_OUT, 0xc80a);
	regmap_write(rt5659->regmap, RT5659_MONO_AMP_CALIB_CTRL_1, 0x1e04);
	regmap_write(rt5659->regmap, RT5659_PWR_MIXER, 0x0000);
	regmap_write(rt5659->regmap, RT5659_PWR_VOL, 0x0000);
	regmap_write(rt5659->regmap, RT5659_PWR_DIG_1, 0x0000);
	regmap_write(rt5659->regmap, RT5659_PWR_DIG_2, 0x0000);
	regmap_write(rt5659->regmap, RT5659_PWR_ANLG_1, 0x003e);
	regmap_write(rt5659->regmap, RT5659_CLASSD_CTRL_1, 0x0060);
	regmap_write(rt5659->regmap, RT5659_CLASSD_0, 0x2021);
	regmap_write(rt5659->regmap, RT5659_GLB_CLK, 0x0000);
	regmap_write(rt5659->regmap, RT5659_MICBIAS_2, 0x0080);
	regmap_write(rt5659->regmap, RT5659_HP_VOL, 0x8080);
	regmap_write(rt5659->regmap, RT5659_HP_CHARGE_PUMP_1, 0x0c16);
}