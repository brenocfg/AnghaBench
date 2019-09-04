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
struct tscs454 {int sysclk_src_id; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM_PLLCTL_PLLISEL ; 
 unsigned int FV_PLLISEL_BCLK ; 
 unsigned int FV_PLLISEL_MCLK1 ; 
 unsigned int FV_PLLISEL_MCLK2 ; 
 unsigned int FV_PLLISEL_XTAL ; 
#define  PLL_INPUT_BCLK 131 
#define  PLL_INPUT_MCLK1 130 
#define  PLL_INPUT_MCLK2 129 
#define  PLL_INPUT_XTAL 128 
 int /*<<< orphan*/  R_PLLCTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int set_sysclk (struct snd_soc_component*) ; 
 struct tscs454* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tscs454_probe(struct snd_soc_component *component)
{
	struct tscs454 *tscs454 = snd_soc_component_get_drvdata(component);
	unsigned int val;
	int ret = 0;

	switch (tscs454->sysclk_src_id) {
	case PLL_INPUT_XTAL:
		val = FV_PLLISEL_XTAL;
		break;
	case PLL_INPUT_MCLK1:
		val = FV_PLLISEL_MCLK1;
		break;
	case PLL_INPUT_MCLK2:
		val = FV_PLLISEL_MCLK2;
		break;
	case PLL_INPUT_BCLK:
		val = FV_PLLISEL_BCLK;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Invalid sysclk src id (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component, R_PLLCTL,
			FM_PLLCTL_PLLISEL, val);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set PLL input (%d)\n", ret);
		return ret;
	}

	if (tscs454->sysclk_src_id < PLL_INPUT_BCLK)
		ret = set_sysclk(component);

	return ret;
}