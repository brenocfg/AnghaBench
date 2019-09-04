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
struct davinci_mcbsp_dev {int clk_div; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_CLKGDV ; 
 int ENODEV ; 
 struct davinci_mcbsp_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int davinci_i2s_dai_set_clkdiv(struct snd_soc_dai *cpu_dai,
				int div_id, int div)
{
	struct davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);

	if (div_id != DAVINCI_MCBSP_CLKGDV)
		return -ENODEV;

	dev->clk_div = div;
	return 0;
}