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

/* Variables and functions */
 int EINVAL ; 
#define  MADERA_OUTCLK_ASYNCCLK 132 
#define  MADERA_OUTCLK_MCLK1 131 
#define  MADERA_OUTCLK_MCLK2 130 
#define  MADERA_OUTCLK_MCLK3 129 
#define  MADERA_OUTCLK_SYSCLK 128 
 int /*<<< orphan*/  MADERA_OUTPUT_RATE_1 ; 
 int MADERA_OUT_CLK_SRC_MASK ; 
 int MADERA_OUT_EXT_CLK_DIV_MASK ; 
 int MADERA_OUT_EXT_CLK_DIV_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int madera_set_outclk(struct snd_soc_component *component,
			     unsigned int source, unsigned int freq)
{
	int div, div_inc, rate;

	switch (source) {
	case MADERA_OUTCLK_SYSCLK:
		dev_dbg(component->dev, "Configured OUTCLK to SYSCLK\n");
		snd_soc_component_update_bits(component, MADERA_OUTPUT_RATE_1,
					      MADERA_OUT_CLK_SRC_MASK, source);
		return 0;
	case MADERA_OUTCLK_ASYNCCLK:
		dev_dbg(component->dev, "Configured OUTCLK to ASYNCCLK\n");
		snd_soc_component_update_bits(component, MADERA_OUTPUT_RATE_1,
					      MADERA_OUT_CLK_SRC_MASK, source);
		return 0;
	case MADERA_OUTCLK_MCLK1:
	case MADERA_OUTCLK_MCLK2:
	case MADERA_OUTCLK_MCLK3:
		break;
	default:
		return -EINVAL;
	}

	if (freq % 4000)
		rate = 5644800;
	else
		rate = 6144000;

	div = 1;
	div_inc = 0;
	while (div <= 8) {
		if (freq / div == rate && !(freq % div)) {
			dev_dbg(component->dev, "Configured %dHz OUTCLK\n", rate);
			snd_soc_component_update_bits(component,
				MADERA_OUTPUT_RATE_1,
				MADERA_OUT_EXT_CLK_DIV_MASK |
				MADERA_OUT_CLK_SRC_MASK,
				(div_inc << MADERA_OUT_EXT_CLK_DIV_SHIFT) |
				source);
			return 0;
		}
		div_inc++;
		div *= 2;
	}

	dev_err(component->dev,
		"Unable to generate %dHz OUTCLK from %dHz MCLK\n",
		rate, freq);
	return -EINVAL;
}