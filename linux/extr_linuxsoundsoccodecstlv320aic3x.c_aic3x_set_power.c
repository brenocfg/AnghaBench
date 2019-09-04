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
struct snd_soc_component {int dummy; } ;
struct aic3x_priv {int power; int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; int /*<<< orphan*/  gpio_reset; } ;
struct TYPE_2__ {unsigned int def; } ;

/* Variables and functions */
 size_t AIC3X_PLL_PROGC_REG ; 
 size_t AIC3X_PLL_PROGD_REG ; 
 size_t AIC3X_RESET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int SOFT_RESET ; 
 TYPE_1__* aic3x_reg ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,size_t) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,size_t,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int aic3x_set_power(struct snd_soc_component *component, int power)
{
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	unsigned int pll_c, pll_d;
	int ret;

	if (power) {
		ret = regulator_bulk_enable(ARRAY_SIZE(aic3x->supplies),
					    aic3x->supplies);
		if (ret)
			goto out;
		aic3x->power = 1;

		if (gpio_is_valid(aic3x->gpio_reset)) {
			udelay(1);
			gpio_set_value(aic3x->gpio_reset, 1);
		}

		/* Sync reg_cache with the hardware */
		regcache_cache_only(aic3x->regmap, false);
		regcache_sync(aic3x->regmap);

		/* Rewrite paired PLL D registers in case cached sync skipped
		 * writing one of them and thus caused other one also not
		 * being written
		 */
		pll_c = snd_soc_component_read32(component, AIC3X_PLL_PROGC_REG);
		pll_d = snd_soc_component_read32(component, AIC3X_PLL_PROGD_REG);
		if (pll_c == aic3x_reg[AIC3X_PLL_PROGC_REG].def ||
			pll_d == aic3x_reg[AIC3X_PLL_PROGD_REG].def) {
			snd_soc_component_write(component, AIC3X_PLL_PROGC_REG, pll_c);
			snd_soc_component_write(component, AIC3X_PLL_PROGD_REG, pll_d);
		}

		/*
		 * Delay is needed to reduce pop-noise after syncing back the
		 * registers
		 */
		mdelay(50);
	} else {
		/*
		 * Do soft reset to this codec instance in order to clear
		 * possible VDD leakage currents in case the supply regulators
		 * remain on
		 */
		snd_soc_component_write(component, AIC3X_RESET, SOFT_RESET);
		regcache_mark_dirty(aic3x->regmap);
		aic3x->power = 0;
		/* HW writes are needless when bias is off */
		regcache_cache_only(aic3x->regmap, true);
		ret = regulator_bulk_disable(ARRAY_SIZE(aic3x->supplies),
					     aic3x->supplies);
	}
out:
	return ret;
}