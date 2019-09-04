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
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SRC_AIF2BCLK ; 
 int /*<<< orphan*/  ARIZONA_CLK_SRC_MCLK1 ; 
 int /*<<< orphan*/  WM5102_FLL1 ; 
 int /*<<< orphan*/  WM5102_FLL1_REFCLK ; 
 unsigned int WM8804_CLKOUT_HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rpi_cirrus_set_fll_refclk(struct snd_soc_card *card,
	struct snd_soc_component *wm5102_component,
	unsigned int clk_freq, unsigned int aif2_freq)
{
	int ret = snd_soc_component_set_pll(wm5102_component,
		WM5102_FLL1_REFCLK,
		ARIZONA_CLK_SRC_MCLK1,
		WM8804_CLKOUT_HZ,
		clk_freq);
	if (ret) {
		dev_err(card->dev,
			"Failed to set FLL1_REFCLK to %d: %d\n",
			clk_freq, ret);
		return ret;
	}

	ret = snd_soc_component_set_pll(wm5102_component,
		WM5102_FLL1,
		ARIZONA_CLK_SRC_AIF2BCLK,
		aif2_freq, clk_freq);
	if (ret)
		dev_err(card->dev,
			"Failed to set FLL1 with Sync Clock %d to %d: %d\n",
			aif2_freq, clk_freq, ret);

	usleep_range(1000, 2000);
	return ret;
}