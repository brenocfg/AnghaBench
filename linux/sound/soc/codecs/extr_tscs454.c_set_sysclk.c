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
struct tscs454 {scalar_t__ sysclk_src_id; unsigned long bclk_freq; int /*<<< orphan*/  sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct pll_ctl {TYPE_1__* settings; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PLL_INPUT_BCLK ; 
 int PLL_REG_SETTINGS_COUNT ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct pll_ctl* get_pll_ctl (unsigned long) ; 
 struct tscs454* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_sysclk(struct snd_soc_component *component)
{
	struct tscs454 *tscs454 = snd_soc_component_get_drvdata(component);
	struct pll_ctl const *pll_ctl;
	unsigned long freq;
	int i;
	int ret;

	if (tscs454->sysclk_src_id < PLL_INPUT_BCLK)
		freq = clk_get_rate(tscs454->sysclk);
	else
		freq = tscs454->bclk_freq;
	pll_ctl = get_pll_ctl(freq);
	if (!pll_ctl) {
		ret = -EINVAL;
		dev_err(component->dev,
				"Invalid PLL input %lu (%d)\n", freq, ret);
		return ret;
	}

	for (i = 0; i < PLL_REG_SETTINGS_COUNT; ++i) {
		ret = snd_soc_component_write(component,
				pll_ctl->settings[i].addr,
				pll_ctl->settings[i].val);
		if (ret < 0) {
			dev_err(component->dev,
					"Failed to set pll setting (%d)\n",
					ret);
			return ret;
		}
	}

	return 0;
}