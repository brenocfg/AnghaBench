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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LM49453_P0_PMC_SETUP_REG ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm49453_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				  unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	u16 pll_clk = 0;

	switch (freq) {
	case 12288000:
	case 26000000:
	case 19200000:
		/* pll clk slection */
		pll_clk = 0;
		break;
	case 48000:
	case 32576:
		/* fll clk slection */
		pll_clk = BIT(4);
		return 0;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG, BIT(4), pll_clk);

	return 0;
}