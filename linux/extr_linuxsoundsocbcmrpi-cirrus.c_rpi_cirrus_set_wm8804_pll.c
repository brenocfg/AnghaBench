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
struct snd_soc_dai {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8804_CLKOUT_HZ ; 
 int /*<<< orphan*/  WM8804_TX_CLKSRC_PLL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_cirrus_set_wm8804_pll(struct snd_soc_card *card,
	struct snd_soc_dai *wm8804_dai, unsigned int rate)
{
	int ret;

	/* use 256fs */
	unsigned int clk_freq = rate * 256;

	ret = snd_soc_dai_set_pll(wm8804_dai, 0, 0,
		WM8804_CLKOUT_HZ, clk_freq);
	if (ret) {
		dev_err(card->dev,
			"Failed to set WM8804 PLL to %d: %d\n", clk_freq, ret);
		return ret;
	}

	/* Set MCLK as PLL Output */
	ret = snd_soc_dai_set_sysclk(wm8804_dai,
		WM8804_TX_CLKSRC_PLL, clk_freq, 0);
	if (ret) {
		dev_err(card->dev,
			"Failed to set MCLK as PLL Output: %d\n", ret);
		return ret;
	}

	return ret;
}