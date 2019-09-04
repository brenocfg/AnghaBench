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
typedef  unsigned int u8 ;
typedef  unsigned long long u64 ;
typedef  unsigned int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct da7219_priv {int mclk_rate; } ;
typedef  unsigned int frac_div ;

/* Variables and functions */
 unsigned long long DA7219_BYTE_MASK ; 
 unsigned long long DA7219_BYTE_SHIFT ; 
 int /*<<< orphan*/  DA7219_PLL_CTRL ; 
 int /*<<< orphan*/  DA7219_PLL_FRAC_BOT ; 
 int /*<<< orphan*/  DA7219_PLL_FRAC_TOP ; 
 unsigned int DA7219_PLL_INDIV_18_TO_36_MHZ ; 
 unsigned int DA7219_PLL_INDIV_18_TO_36_MHZ_VAL ; 
 unsigned int DA7219_PLL_INDIV_2_TO_4_5_MHZ ; 
 unsigned int DA7219_PLL_INDIV_2_TO_4_5_MHZ_VAL ; 
 unsigned int DA7219_PLL_INDIV_36_TO_54_MHZ ; 
 unsigned int DA7219_PLL_INDIV_36_TO_54_MHZ_VAL ; 
 unsigned int DA7219_PLL_INDIV_4_5_TO_9_MHZ ; 
 unsigned int DA7219_PLL_INDIV_4_5_TO_9_MHZ_VAL ; 
 unsigned int DA7219_PLL_INDIV_9_TO_18_MHZ ; 
 unsigned int DA7219_PLL_INDIV_9_TO_18_MHZ_VAL ; 
 int DA7219_PLL_INDIV_MASK ; 
 int /*<<< orphan*/  DA7219_PLL_INTEGER ; 
 unsigned int DA7219_PLL_MODE_BYPASS ; 
 int DA7219_PLL_MODE_MASK ; 
 unsigned int DA7219_PLL_MODE_NORMAL ; 
 unsigned int DA7219_PLL_MODE_SRM ; 
#define  DA7219_SYSCLK_MCLK 130 
#define  DA7219_SYSCLK_PLL 129 
#define  DA7219_SYSCLK_PLL_SRM 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned int) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

int da7219_set_pll(struct snd_soc_component *component, int source, unsigned int fout)
{
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	u8 pll_ctrl, indiv_bits, indiv;
	u8 pll_frac_top, pll_frac_bot, pll_integer;
	u32 freq_ref;
	u64 frac_div;

	/* Verify 2MHz - 54MHz MCLK provided, and set input divider */
	if (da7219->mclk_rate < 2000000) {
		dev_err(component->dev, "PLL input clock %d below valid range\n",
			da7219->mclk_rate);
		return -EINVAL;
	} else if (da7219->mclk_rate <= 4500000) {
		indiv_bits = DA7219_PLL_INDIV_2_TO_4_5_MHZ;
		indiv = DA7219_PLL_INDIV_2_TO_4_5_MHZ_VAL;
	} else if (da7219->mclk_rate <= 9000000) {
		indiv_bits = DA7219_PLL_INDIV_4_5_TO_9_MHZ;
		indiv = DA7219_PLL_INDIV_4_5_TO_9_MHZ_VAL;
	} else if (da7219->mclk_rate <= 18000000) {
		indiv_bits = DA7219_PLL_INDIV_9_TO_18_MHZ;
		indiv = DA7219_PLL_INDIV_9_TO_18_MHZ_VAL;
	} else if (da7219->mclk_rate <= 36000000) {
		indiv_bits = DA7219_PLL_INDIV_18_TO_36_MHZ;
		indiv = DA7219_PLL_INDIV_18_TO_36_MHZ_VAL;
	} else if (da7219->mclk_rate <= 54000000) {
		indiv_bits = DA7219_PLL_INDIV_36_TO_54_MHZ;
		indiv = DA7219_PLL_INDIV_36_TO_54_MHZ_VAL;
	} else {
		dev_err(component->dev, "PLL input clock %d above valid range\n",
			da7219->mclk_rate);
		return -EINVAL;
	}
	freq_ref = (da7219->mclk_rate / indiv);
	pll_ctrl = indiv_bits;

	/* Configure PLL */
	switch (source) {
	case DA7219_SYSCLK_MCLK:
		pll_ctrl |= DA7219_PLL_MODE_BYPASS;
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_INDIV_MASK |
				    DA7219_PLL_MODE_MASK, pll_ctrl);
		return 0;
	case DA7219_SYSCLK_PLL:
		pll_ctrl |= DA7219_PLL_MODE_NORMAL;
		break;
	case DA7219_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7219_PLL_MODE_SRM;
		break;
	default:
		dev_err(component->dev, "Invalid PLL config\n");
		return -EINVAL;
	}

	/* Calculate dividers for PLL */
	pll_integer = fout / freq_ref;
	frac_div = (u64)(fout % freq_ref) * 8192ULL;
	do_div(frac_div, freq_ref);
	pll_frac_top = (frac_div >> DA7219_BYTE_SHIFT) & DA7219_BYTE_MASK;
	pll_frac_bot = (frac_div) & DA7219_BYTE_MASK;

	/* Write PLL config & dividers */
	snd_soc_component_write(component, DA7219_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_write(component, DA7219_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_write(component, DA7219_PLL_INTEGER, pll_integer);
	snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
			    DA7219_PLL_INDIV_MASK | DA7219_PLL_MODE_MASK,
			    pll_ctrl);

	return 0;
}