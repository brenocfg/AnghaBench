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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct nau8810_pll {int pll_int; int pll_frac; int mclk_scaler; scalar_t__ pre_factor; } ;
struct nau8810 {int /*<<< orphan*/  dev; struct nau8810_pll pll; struct regmap* regmap; } ;

/* Variables and functions */
 int NAU8810_CLKM_MASK ; 
 int NAU8810_CLKM_PLL ; 
 int NAU8810_MCLKSEL_MASK ; 
 int NAU8810_MCLKSEL_SFT ; 
 int NAU8810_PLLK1_MASK ; 
 int NAU8810_PLLK1_SFT ; 
 int NAU8810_PLLK2_MASK ; 
 int NAU8810_PLLK2_SFT ; 
 int NAU8810_PLLK3_MASK ; 
 int NAU8810_PLLMCLK_DIV2 ; 
 int NAU8810_PLLN_MASK ; 
 int /*<<< orphan*/  NAU8810_REG_CLOCK ; 
 int /*<<< orphan*/  NAU8810_REG_PLLK1 ; 
 int /*<<< orphan*/  NAU8810_REG_PLLK2 ; 
 int /*<<< orphan*/  NAU8810_REG_PLLK3 ; 
 int /*<<< orphan*/  NAU8810_REG_PLLN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,scalar_t__) ; 
 int nau8810_calc_pll (unsigned int,int,struct nau8810_pll*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct nau8810* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8810_set_pll(struct snd_soc_dai *codec_dai, int pll_id,
	int source, unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = codec_dai->component;
	struct nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	struct regmap *map = nau8810->regmap;
	struct nau8810_pll *pll_param = &nau8810->pll;
	int ret, fs;

	fs = freq_out / 256;
	ret = nau8810_calc_pll(freq_in, fs, pll_param);
	if (ret < 0) {
		dev_err(nau8810->dev, "Unsupported input clock %d\n", freq_in);
		return ret;
	}
	dev_info(nau8810->dev, "pll_int=%x pll_frac=%x mclk_scaler=%x pre_factor=%x\n",
		pll_param->pll_int, pll_param->pll_frac, pll_param->mclk_scaler,
		pll_param->pre_factor);

	regmap_update_bits(map, NAU8810_REG_PLLN,
		NAU8810_PLLMCLK_DIV2 | NAU8810_PLLN_MASK,
		(pll_param->pre_factor ? NAU8810_PLLMCLK_DIV2 : 0) |
		pll_param->pll_int);
	regmap_write(map, NAU8810_REG_PLLK1,
		(pll_param->pll_frac >> NAU8810_PLLK1_SFT) &
		NAU8810_PLLK1_MASK);
	regmap_write(map, NAU8810_REG_PLLK2,
		(pll_param->pll_frac >> NAU8810_PLLK2_SFT) &
		NAU8810_PLLK2_MASK);
	regmap_write(map, NAU8810_REG_PLLK3,
		pll_param->pll_frac & NAU8810_PLLK3_MASK);
	regmap_update_bits(map, NAU8810_REG_CLOCK, NAU8810_MCLKSEL_MASK,
		pll_param->mclk_scaler << NAU8810_MCLKSEL_SFT);
	regmap_update_bits(map, NAU8810_REG_CLOCK,
		NAU8810_CLKM_MASK, NAU8810_CLKM_PLL);

	return 0;
}