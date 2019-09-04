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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct da732x_priv {int pll_en; int sysclk; } ;
typedef  unsigned int frac_div ;

/* Variables and functions */
 unsigned long long DA732X_1BYTE_SHIFT ; 
 unsigned int DA732X_PLL_BYPASS ; 
 int /*<<< orphan*/  DA732X_PLL_EN ; 
 int /*<<< orphan*/  DA732X_REG_PLL_CTRL ; 
 int /*<<< orphan*/  DA732X_REG_PLL_DIV_HI ; 
 int /*<<< orphan*/  DA732X_REG_PLL_DIV_LO ; 
 int /*<<< orphan*/  DA732X_REG_PLL_DIV_MID ; 
 int DA732X_SRCCLK_MCLK ; 
 unsigned long long DA732X_U8_MASK ; 
 int EBUSY ; 
 int EINVAL ; 
 int da732x_get_input_div (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 struct da732x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da732x_set_dai_pll(struct snd_soc_component *component, int pll_id,
			      int source, unsigned int freq_in,
			      unsigned int freq_out)
{
	struct da732x_priv *da732x = snd_soc_component_get_drvdata(component);
	int fref, indiv;
	u8 div_lo, div_mid, div_hi;
	u64 frac_div;

	/* Disable PLL */
	if (freq_out == 0) {
		snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL,
				    DA732X_PLL_EN, 0);
		da732x->pll_en = false;
		return 0;
	}

	if (da732x->pll_en)
		return -EBUSY;

	if (source == DA732X_SRCCLK_MCLK) {
		/* Validate Sysclk rate */
		switch (da732x->sysclk) {
		case 11290000:
		case 12288000:
		case 22580000:
		case 24576000:
		case 45160000:
		case 49152000:
			snd_soc_component_write(component, DA732X_REG_PLL_CTRL,
				      DA732X_PLL_BYPASS);
			return 0;
		default:
			dev_err(component->dev,
				"Cannot use PLL Bypass, invalid SYSCLK rate\n");
			return -EINVAL;
		}
	}

	indiv = da732x_get_input_div(component, da732x->sysclk);
	if (indiv < 0)
		return indiv;

	fref = (da732x->sysclk / indiv);
	div_hi = freq_out / fref;
	frac_div = (u64)(freq_out % fref) * 8192ULL;
	do_div(frac_div, fref);
	div_mid = (frac_div >> DA732X_1BYTE_SHIFT) & DA732X_U8_MASK;
	div_lo = (frac_div) & DA732X_U8_MASK;

	snd_soc_component_write(component, DA732X_REG_PLL_DIV_LO, div_lo);
	snd_soc_component_write(component, DA732X_REG_PLL_DIV_MID, div_mid);
	snd_soc_component_write(component, DA732X_REG_PLL_DIV_HI, div_hi);

	snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL, DA732X_PLL_EN,
			    DA732X_PLL_EN);

	da732x->pll_en = true;

	return 0;
}