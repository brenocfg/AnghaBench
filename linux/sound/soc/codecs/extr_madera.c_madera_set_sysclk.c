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
struct snd_soc_component {int dummy; } ;
struct madera_priv {int sysclk; int asyncclk; int dspclk; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MADERA_ASYNC_CLOCK_1 ; 
#define  MADERA_CLK_ASYNCCLK_1 133 
#define  MADERA_CLK_ASYNC_OPCLK 132 
#define  MADERA_CLK_DSPCLK 131 
#define  MADERA_CLK_OPCLK 130 
#define  MADERA_CLK_OUTCLK 129 
#define  MADERA_CLK_SYSCLK_1 128 
 unsigned int MADERA_DSP_CLOCK_1 ; 
 int /*<<< orphan*/  MADERA_DSP_CLOCK_2 ; 
 unsigned int MADERA_SYSCLK_FRAC ; 
 unsigned int MADERA_SYSCLK_FREQ_MASK ; 
 unsigned int MADERA_SYSCLK_SRC_MASK ; 
 int MADERA_SYSCLK_SRC_SHIFT ; 
 unsigned int MADERA_SYSTEM_CLOCK_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int madera_get_dspclk_setting (struct madera*,unsigned int,unsigned int*) ; 
 int madera_get_sysclk_setting (unsigned int) ; 
 int madera_set_opclk (struct snd_soc_component*,int,unsigned int) ; 
 int madera_set_outclk (struct snd_soc_component*,int,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int madera_set_sysclk(struct snd_soc_component *component, int clk_id,
		      int source, unsigned int freq, int dir)
{
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	char *name;
	unsigned int reg, clock_2_val = 0;
	unsigned int mask = MADERA_SYSCLK_FREQ_MASK | MADERA_SYSCLK_SRC_MASK;
	unsigned int val = source << MADERA_SYSCLK_SRC_SHIFT;
	int clk_freq_sel, *clk;
	int ret = 0;

	switch (clk_id) {
	case MADERA_CLK_SYSCLK_1:
		name = "SYSCLK";
		reg = MADERA_SYSTEM_CLOCK_1;
		clk = &priv->sysclk;
		clk_freq_sel = madera_get_sysclk_setting(freq);
		mask |= MADERA_SYSCLK_FRAC;
		break;
	case MADERA_CLK_ASYNCCLK_1:
		name = "ASYNCCLK";
		reg = MADERA_ASYNC_CLOCK_1;
		clk = &priv->asyncclk;
		clk_freq_sel = madera_get_sysclk_setting(freq);
		break;
	case MADERA_CLK_DSPCLK:
		name = "DSPCLK";
		reg = MADERA_DSP_CLOCK_1;
		clk = &priv->dspclk;
		clk_freq_sel = madera_get_dspclk_setting(madera, freq,
							 &clock_2_val);
		break;
	case MADERA_CLK_OPCLK:
	case MADERA_CLK_ASYNC_OPCLK:
		return madera_set_opclk(component, clk_id, freq);
	case MADERA_CLK_OUTCLK:
		return madera_set_outclk(component, source, freq);
	default:
		return -EINVAL;
	}

	if (clk_freq_sel < 0) {
		dev_err(madera->dev,
			"Failed to get clk setting for %dHZ\n", freq);
		return clk_freq_sel;
	}

	*clk = freq;

	if (freq == 0) {
		dev_dbg(madera->dev, "%s cleared\n", name);
		return 0;
	}

	val |= clk_freq_sel;

	if (clock_2_val) {
		ret = regmap_write(madera->regmap, MADERA_DSP_CLOCK_2,
				   clock_2_val);
		if (ret) {
			dev_err(madera->dev,
				"Failed to write DSP_CONFIG2: %d\n", ret);
			return ret;
		}

		/*
		 * We're using the frequency setting in MADERA_DSP_CLOCK_2 so
		 * don't change the frequency select bits in MADERA_DSP_CLOCK_1
		 */
		mask = MADERA_SYSCLK_SRC_MASK;
	}

	if (freq % 6144000)
		val |= MADERA_SYSCLK_FRAC;

	dev_dbg(madera->dev, "%s set to %uHz\n", name, freq);

	return regmap_update_bits(madera->regmap, reg, mask, val);
}