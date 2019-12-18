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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct adau1701 {unsigned int pll_clkdiv; int /*<<< orphan*/  regmap; int /*<<< orphan*/  sigmadsp; int /*<<< orphan*/  gpio_nreset; int /*<<< orphan*/ * gpio_pll_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_DACSET ; 
 int /*<<< orphan*/  ADAU1701_DACSET_DACINIT ; 
 int /*<<< orphan*/  ADAU1701_DSPCTRL ; 
 int /*<<< orphan*/  ADAU1701_DSPCTRL_CR ; 
 unsigned int ADAU1707_CLKDIV_UNSET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmadsp_reset (int /*<<< orphan*/ ) ; 
 int sigmadsp_setup (int /*<<< orphan*/ ,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int adau1701_reset(struct snd_soc_component *component, unsigned int clkdiv,
	unsigned int rate)
{
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	int ret;

	sigmadsp_reset(adau1701->sigmadsp);

	if (clkdiv != ADAU1707_CLKDIV_UNSET &&
	    gpio_is_valid(adau1701->gpio_pll_mode[0]) &&
	    gpio_is_valid(adau1701->gpio_pll_mode[1])) {
		switch (clkdiv) {
		case 64:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			break;
		case 256:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			break;
		case 384:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			break;
		case 0:	/* fallback */
		case 512:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			break;
		}
	}

	adau1701->pll_clkdiv = clkdiv;

	if (gpio_is_valid(adau1701->gpio_nreset)) {
		gpio_set_value_cansleep(adau1701->gpio_nreset, 0);
		/* minimum reset time is 20ns */
		udelay(1);
		gpio_set_value_cansleep(adau1701->gpio_nreset, 1);
		/* power-up time may be as long as 85ms */
		mdelay(85);
	}

	/*
	 * Postpone the firmware download to a point in time when we
	 * know the correct PLL setup
	 */
	if (clkdiv != ADAU1707_CLKDIV_UNSET) {
		ret = sigmadsp_setup(adau1701->sigmadsp, rate);
		if (ret) {
			dev_warn(component->dev, "Failed to load firmware\n");
			return ret;
		}
	}

	regmap_write(adau1701->regmap, ADAU1701_DACSET, ADAU1701_DACSET_DACINIT);
	regmap_write(adau1701->regmap, ADAU1701_DSPCTRL, ADAU1701_DSPCTRL_CR);

	regcache_mark_dirty(adau1701->regmap);
	regcache_sync(adau1701->regmap);

	return 0;
}