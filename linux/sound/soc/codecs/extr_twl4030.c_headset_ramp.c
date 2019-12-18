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
struct twl4030_priv {unsigned int sysclk; struct twl4030_codec_data* pdata; } ;
struct twl4030_codec_data {int /*<<< orphan*/  hs_extmute_gpio; scalar_t__ hs_extmute; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned char TWL4030_EXTMUTE ; 
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
 unsigned char TWL4030_RAMP_DELAY ; 
 unsigned char TWL4030_RAMP_EN ; 
 int /*<<< orphan*/  TWL4030_REG_HS_GAIN_SET ; 
 int /*<<< orphan*/  TWL4030_REG_HS_POPN_SET ; 
 unsigned char TWL4030_VMID_EN ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned char twl4030_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_wait_ms (unsigned int) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void headset_ramp(struct snd_soc_component *component, int ramp)
{
	unsigned char hs_gain, hs_pop;
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	struct twl4030_codec_data *pdata = twl4030->pdata;
	/* Base values for ramp delay calculation: 2^19 - 2^26 */
	unsigned int ramp_base[] = {524288, 1048576, 2097152, 4194304,
				    8388608, 16777216, 33554432, 67108864};
	unsigned int delay;

	hs_gain = twl4030_read(component, TWL4030_REG_HS_GAIN_SET);
	hs_pop = twl4030_read(component, TWL4030_REG_HS_POPN_SET);
	delay = (ramp_base[(hs_pop & TWL4030_RAMP_DELAY) >> 2] /
		twl4030->sysclk) + 1;

	/* Enable external mute control, this dramatically reduces
	 * the pop-noise */
	if (pdata && pdata->hs_extmute) {
		if (gpio_is_valid(pdata->hs_extmute_gpio)) {
			gpio_set_value(pdata->hs_extmute_gpio, 1);
		} else {
			hs_pop |= TWL4030_EXTMUTE;
			twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}

	if (ramp) {
		/* Headset ramp-up according to the TRM */
		hs_pop |= TWL4030_VMID_EN;
		twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Actually write to the register */
		twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain,
				 TWL4030_REG_HS_GAIN_SET);
		hs_pop |= TWL4030_RAMP_EN;
		twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay time + 1, so the VMID can settle */
		twl4030_wait_ms(delay);
	} else {
		/* Headset ramp-down _not_ according to
		 * the TRM, but in a way that it is working */
		hs_pop &= ~TWL4030_RAMP_EN;
		twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay time + 1, so the VMID can settle */
		twl4030_wait_ms(delay);
		/* Bypass the reg_cache to mute the headset */
		twl_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain & (~0x0f),
				 TWL4030_REG_HS_GAIN_SET);

		hs_pop &= ~TWL4030_VMID_EN;
		twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
	}

	/* Disable external mute */
	if (pdata && pdata->hs_extmute) {
		if (gpio_is_valid(pdata->hs_extmute_gpio)) {
			gpio_set_value(pdata->hs_extmute_gpio, 0);
		} else {
			hs_pop &= ~TWL4030_EXTMUTE;
			twl4030_write(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}
}