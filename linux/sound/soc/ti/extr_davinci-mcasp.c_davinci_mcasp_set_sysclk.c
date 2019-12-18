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
struct davinci_mcasp {unsigned int sysclk_freq; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCLKRE ; 
 int /*<<< orphan*/  AHCLKXE ; 
 int /*<<< orphan*/  DAVINCI_MCASP_AHCLKRCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_AHCLKXCTL_REG ; 
 int /*<<< orphan*/  PIN_BIT_AHCLKX ; 
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct davinci_mcasp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int davinci_mcasp_set_sysclk(struct snd_soc_dai *dai, int clk_id,
				    unsigned int freq, int dir)
{
	struct davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(dai);

	pm_runtime_get_sync(mcasp->dev);
	if (dir == SND_SOC_CLOCK_OUT) {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG, AHCLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG, AHCLKRE);
		set_bit(PIN_BIT_AHCLKX, &mcasp->pdir);
	} else {
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_AHCLKXCTL_REG, AHCLKXE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_AHCLKRCTL_REG, AHCLKRE);
		clear_bit(PIN_BIT_AHCLKX, &mcasp->pdir);
	}

	mcasp->sysclk_freq = freq;

	pm_runtime_put(mcasp->dev);
	return 0;
}