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
struct madera_priv {int sysclk; int asyncclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
#define  MADERA_CLK_ASYNC_OPCLK 129 
#define  MADERA_CLK_OPCLK 128 
 unsigned int MADERA_OPCLK_DIV_MASK ; 
 int MADERA_OPCLK_DIV_SHIFT ; 
 unsigned int MADERA_OPCLK_SEL_MASK ; 
 unsigned int MADERA_OUTPUT_ASYNC_CLOCK ; 
 unsigned int MADERA_OUTPUT_SYSTEM_CLOCK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int* madera_opclk_ref_44k1_rates ; 
 unsigned int* madera_opclk_ref_48k_rates ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int madera_set_opclk(struct snd_soc_component *component,
			    unsigned int clk, unsigned int freq)
{
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	unsigned int mask = MADERA_OPCLK_DIV_MASK | MADERA_OPCLK_SEL_MASK;
	unsigned int reg, val;
	const unsigned int *rates;
	int ref, div, refclk;

	BUILD_BUG_ON(ARRAY_SIZE(madera_opclk_ref_48k_rates) !=
		     ARRAY_SIZE(madera_opclk_ref_44k1_rates));

	switch (clk) {
	case MADERA_CLK_OPCLK:
		reg = MADERA_OUTPUT_SYSTEM_CLOCK;
		refclk = priv->sysclk;
		break;
	case MADERA_CLK_ASYNC_OPCLK:
		reg = MADERA_OUTPUT_ASYNC_CLOCK;
		refclk = priv->asyncclk;
		break;
	default:
		return -EINVAL;
	}

	if (refclk % 4000)
		rates = madera_opclk_ref_44k1_rates;
	else
		rates = madera_opclk_ref_48k_rates;

	for (ref = 0; ref < ARRAY_SIZE(madera_opclk_ref_48k_rates); ++ref) {
		if (rates[ref] > refclk)
			continue;

		div = 2;
		while ((rates[ref] / div >= freq) && (div <= 30)) {
			if (rates[ref] / div == freq) {
				dev_dbg(component->dev, "Configured %dHz OPCLK\n",
					freq);

				val = (div << MADERA_OPCLK_DIV_SHIFT) | ref;

				snd_soc_component_update_bits(component, reg,
							      mask, val);
				return 0;
			}
			div += 2;
		}
	}

	dev_err(component->dev, "Unable to generate %dHz OPCLK\n", freq);

	return -EINVAL;
}