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
struct arizona_priv {int sysclk; int asyncclk; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARIZONA_ASYNC_CLOCK_1 ; 
 unsigned int ARIZONA_CLK_12MHZ ; 
 unsigned int ARIZONA_CLK_147MHZ ; 
 unsigned int ARIZONA_CLK_24MHZ ; 
 unsigned int ARIZONA_CLK_49MHZ ; 
 unsigned int ARIZONA_CLK_73MHZ ; 
 unsigned int ARIZONA_CLK_98MHZ ; 
#define  ARIZONA_CLK_ASYNCCLK 131 
#define  ARIZONA_CLK_ASYNC_OPCLK 130 
#define  ARIZONA_CLK_OPCLK 129 
#define  ARIZONA_CLK_SYSCLK 128 
 unsigned int ARIZONA_SYSCLK_FRAC ; 
 unsigned int ARIZONA_SYSCLK_FREQ_MASK ; 
 unsigned int ARIZONA_SYSCLK_FREQ_SHIFT ; 
 unsigned int ARIZONA_SYSCLK_SRC_MASK ; 
 int ARIZONA_SYSCLK_SRC_SHIFT ; 
 unsigned int ARIZONA_SYSTEM_CLOCK_1 ; 
 int EINVAL ; 
 int arizona_set_opclk (struct snd_soc_component*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int arizona_set_sysclk(struct snd_soc_component *component, int clk_id,
		       int source, unsigned int freq, int dir)
{
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	char *name;
	unsigned int reg;
	unsigned int mask = ARIZONA_SYSCLK_FREQ_MASK | ARIZONA_SYSCLK_SRC_MASK;
	unsigned int val = source << ARIZONA_SYSCLK_SRC_SHIFT;
	int *clk;

	switch (clk_id) {
	case ARIZONA_CLK_SYSCLK:
		name = "SYSCLK";
		reg = ARIZONA_SYSTEM_CLOCK_1;
		clk = &priv->sysclk;
		mask |= ARIZONA_SYSCLK_FRAC;
		break;
	case ARIZONA_CLK_ASYNCCLK:
		name = "ASYNCCLK";
		reg = ARIZONA_ASYNC_CLOCK_1;
		clk = &priv->asyncclk;
		break;
	case ARIZONA_CLK_OPCLK:
	case ARIZONA_CLK_ASYNC_OPCLK:
		return arizona_set_opclk(component, clk_id, freq);
	default:
		return -EINVAL;
	}

	switch (freq) {
	case  5644800:
	case  6144000:
		break;
	case 11289600:
	case 12288000:
		val |= ARIZONA_CLK_12MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 22579200:
	case 24576000:
		val |= ARIZONA_CLK_24MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 45158400:
	case 49152000:
		val |= ARIZONA_CLK_49MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 67737600:
	case 73728000:
		val |= ARIZONA_CLK_73MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 90316800:
	case 98304000:
		val |= ARIZONA_CLK_98MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 135475200:
	case 147456000:
		val |= ARIZONA_CLK_147MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		break;
	case 0:
		dev_dbg(arizona->dev, "%s cleared\n", name);
		*clk = freq;
		return 0;
	default:
		return -EINVAL;
	}

	*clk = freq;

	if (freq % 6144000)
		val |= ARIZONA_SYSCLK_FRAC;

	dev_dbg(arizona->dev, "%s set to %uHz", name, freq);

	return regmap_update_bits(arizona->regmap, reg, mask, val);
}