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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct nau8822_pll {int mclk_scaler; } ;
struct nau8822 {int div_id; int sysclk; struct nau8822_pll pll; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NAU8822_CLKM_MASK ; 
 int NAU8822_CLKM_MCLK ; 
 int NAU8822_CLKM_PLL ; 
#define  NAU8822_CLK_MCLK 129 
#define  NAU8822_CLK_PLL 128 
 int /*<<< orphan*/  NAU8822_MCLKSEL_MASK ; 
 int NAU8822_MCLKSEL_SFT ; 
 int /*<<< orphan*/  NAU8822_REG_CLOCKING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int* nau8822_mclk_scaler ; 
 struct nau8822* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nau8822_config_clkdiv(struct snd_soc_dai *dai, int div, int rate)
{
	struct snd_soc_component *component = dai->component;
	struct nau8822 *nau8822 = snd_soc_component_get_drvdata(component);
	struct nau8822_pll *pll = &nau8822->pll;
	int i, sclk, imclk;

	switch (nau8822->div_id) {
	case NAU8822_CLK_MCLK:
		/* Configure the master clock prescaler div to make system
		 * clock to approximate the internal master clock (IMCLK);
		 * and large or equal to IMCLK.
		 */
		div = 0;
		imclk = rate * 256;
		for (i = 1; i < ARRAY_SIZE(nau8822_mclk_scaler); i++) {
			sclk = (nau8822->sysclk * 10) /	nau8822_mclk_scaler[i];
			if (sclk < imclk)
				break;
			div = i;
		}
		dev_dbg(component->dev, "master clock prescaler %x for fs %d\n",
			div, rate);

		/* master clock from MCLK and disable PLL */
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_MCLKSEL_MASK,
			(div << NAU8822_MCLKSEL_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_CLKM_MASK,
			NAU8822_CLKM_MCLK);
		break;

	case NAU8822_CLK_PLL:
		/* master clock from PLL and enable PLL */
		if (pll->mclk_scaler != div) {
			dev_err(component->dev,
			"master clock prescaler not meet PLL parameters\n");
			return -EINVAL;
		}
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_MCLKSEL_MASK,
			(div << NAU8822_MCLKSEL_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_CLKM_MASK,
			NAU8822_CLKM_PLL);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}