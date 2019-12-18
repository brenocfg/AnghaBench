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
struct cs43130_private {unsigned int mclk; int pll_bypass; } ;

/* Variables and functions */
#define  CS43130_MCLK_22M 129 
#define  CS43130_MCLK_24M 128 
 int CS43130_MCLK_SRC_EXT ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs43130_component_set_sysclk(struct snd_soc_component *component,
				    int clk_id, int source, unsigned int freq,
				    int dir)
{
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "clk_id = %d, source = %d, freq = %d, dir = %d\n",
		clk_id, source, freq, dir);

	switch (freq) {
	case CS43130_MCLK_22M:
	case CS43130_MCLK_24M:
		cs43130->mclk = freq;
		break;
	default:
		dev_err(component->dev, "Invalid MCLK INT freq: %u\n", freq);
		return -EINVAL;
	}

	if (source == CS43130_MCLK_SRC_EXT) {
		cs43130->pll_bypass = true;
	} else {
		dev_err(component->dev, "Invalid MCLK source\n");
		return -EINVAL;
	}

	return 0;
}