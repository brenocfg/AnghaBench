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
struct wm_adsp {int num; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct madera_priv {unsigned int* adsp_rate_cache; TYPE_1__* madera; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CS47L35 130 
#define  CS47L85 129 
 unsigned int MADERA_DSP_CLK_SEL_MASK ; 
 unsigned int MADERA_DSP_CLK_SEL_SHIFT ; 
 scalar_t__ MADERA_DSP_CONFIG_1_OFFS ; 
 scalar_t__ MADERA_DSP_CONFIG_2_OFFS ; 
 unsigned int MADERA_DSP_RATE_MASK ; 
 unsigned int MADERA_DSP_RATE_SHIFT ; 
#define  WM1840 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int madera_write_adsp_clk_setting(struct madera_priv *priv,
					 struct wm_adsp *dsp,
					 unsigned int freq)
{
	unsigned int val;
	unsigned int mask = MADERA_DSP_RATE_MASK;
	int ret;

	val = priv->adsp_rate_cache[dsp->num - 1] << MADERA_DSP_RATE_SHIFT;

	switch (priv->madera->type) {
	case CS47L35:
	case CS47L85:
	case WM1840:
		/* use legacy frequency registers */
		mask |= MADERA_DSP_CLK_SEL_MASK;
		val |= (freq << MADERA_DSP_CLK_SEL_SHIFT);
		break;
	default:
		/* Configure exact dsp frequency */
		dev_dbg(priv->madera->dev, "Set DSP frequency to 0x%x\n", freq);

		ret = regmap_write(dsp->regmap,
				   dsp->base + MADERA_DSP_CONFIG_2_OFFS, freq);
		if (ret)
			goto err;
		break;
	}

	ret = regmap_update_bits(dsp->regmap,
				 dsp->base + MADERA_DSP_CONFIG_1_OFFS,
				 mask, val);
	if (ret)
		goto err;

	dev_dbg(priv->madera->dev, "Set DSP clocking to 0x%x\n", val);

	return 0;

err:
	dev_err(dsp->dev, "Failed to set DSP%d clock: %d\n", dsp->num, ret);

	return ret;
}