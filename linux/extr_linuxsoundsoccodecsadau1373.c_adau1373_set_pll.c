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
typedef  int uint8_t ;
struct snd_soc_component {int dummy; } ;
struct adau1373 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_CLK_SRC_DIV (int) ; 
 int /*<<< orphan*/  ADAU1373_DPLL_CTRL (int) ; 
#define  ADAU1373_PLL1 141 
#define  ADAU1373_PLL2 140 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL1 (int) ; 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL2 (int) ; 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL3 (int) ; 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL4 (int) ; 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL5 (int) ; 
 int /*<<< orphan*/  ADAU1373_PLL_CTRL6 (int) ; 
 int ADAU1373_PLL_CTRL6_DPLL_BYPASS ; 
#define  ADAU1373_PLL_SRC_BCLK1 139 
#define  ADAU1373_PLL_SRC_BCLK2 138 
#define  ADAU1373_PLL_SRC_BCLK3 137 
#define  ADAU1373_PLL_SRC_GPIO1 136 
#define  ADAU1373_PLL_SRC_GPIO2 135 
#define  ADAU1373_PLL_SRC_GPIO3 134 
#define  ADAU1373_PLL_SRC_GPIO4 133 
#define  ADAU1373_PLL_SRC_LRCLK1 132 
#define  ADAU1373_PLL_SRC_LRCLK2 131 
#define  ADAU1373_PLL_SRC_LRCLK3 130 
#define  ADAU1373_PLL_SRC_MCLK1 129 
#define  ADAU1373_PLL_SRC_MCLK2 128 
 int EINVAL ; 
 int adau_calc_pll_cfg (unsigned int,unsigned int,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adau1373* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1373_set_pll(struct snd_soc_component *component, int pll_id,
	int source, unsigned int freq_in, unsigned int freq_out)
{
	struct adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	unsigned int dpll_div = 0;
	uint8_t pll_regs[5];
	int ret;

	switch (pll_id) {
	case ADAU1373_PLL1:
	case ADAU1373_PLL2:
		break;
	default:
		return -EINVAL;
	}

	switch (source) {
	case ADAU1373_PLL_SRC_BCLK1:
	case ADAU1373_PLL_SRC_BCLK2:
	case ADAU1373_PLL_SRC_BCLK3:
	case ADAU1373_PLL_SRC_LRCLK1:
	case ADAU1373_PLL_SRC_LRCLK2:
	case ADAU1373_PLL_SRC_LRCLK3:
	case ADAU1373_PLL_SRC_MCLK1:
	case ADAU1373_PLL_SRC_MCLK2:
	case ADAU1373_PLL_SRC_GPIO1:
	case ADAU1373_PLL_SRC_GPIO2:
	case ADAU1373_PLL_SRC_GPIO3:
	case ADAU1373_PLL_SRC_GPIO4:
		break;
	default:
		return -EINVAL;
	}

	if (freq_in < 7813 || freq_in > 27000000)
		return -EINVAL;

	if (freq_out < 45158000 || freq_out > 49152000)
		return -EINVAL;

	/* APLL input needs to be >= 8Mhz, so in case freq_in is less we use the
	 * DPLL to get it there. DPLL_out = (DPLL_in / div) * 1024 */
	while (freq_in < 8000000) {
		freq_in *= 2;
		dpll_div++;
	}

	ret = adau_calc_pll_cfg(freq_in, freq_out, pll_regs);
	if (ret)
		return -EINVAL;

	if (dpll_div) {
		dpll_div = 11 - dpll_div;
		regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
			ADAU1373_PLL_CTRL6_DPLL_BYPASS, 0);
	} else {
		regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
			ADAU1373_PLL_CTRL6_DPLL_BYPASS,
			ADAU1373_PLL_CTRL6_DPLL_BYPASS);
	}

	regmap_write(adau1373->regmap, ADAU1373_DPLL_CTRL(pll_id),
		(source << 4) | dpll_div);
	regmap_write(adau1373->regmap, ADAU1373_PLL_CTRL1(pll_id), pll_regs[0]);
	regmap_write(adau1373->regmap, ADAU1373_PLL_CTRL2(pll_id), pll_regs[1]);
	regmap_write(adau1373->regmap, ADAU1373_PLL_CTRL3(pll_id), pll_regs[2]);
	regmap_write(adau1373->regmap, ADAU1373_PLL_CTRL4(pll_id), pll_regs[3]);
	regmap_write(adau1373->regmap, ADAU1373_PLL_CTRL5(pll_id), pll_regs[4]);

	/* Set sysclk to pll_rate / 4 */
	regmap_update_bits(adau1373->regmap, ADAU1373_CLK_SRC_DIV(pll_id), 0x3f, 0x09);

	return 0;
}