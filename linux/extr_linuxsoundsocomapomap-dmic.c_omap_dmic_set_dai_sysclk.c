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
struct omap_dmic {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_CLOCK_IN ; 
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int omap_dmic_select_fclk (struct omap_dmic*,int,unsigned int) ; 
 int omap_dmic_select_outclk (struct omap_dmic*,int,unsigned int) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_dmic_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				    unsigned int freq, int dir)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	if (dir == SND_SOC_CLOCK_IN)
		return omap_dmic_select_fclk(dmic, clk_id, freq);
	else if (dir == SND_SOC_CLOCK_OUT)
		return omap_dmic_select_outclk(dmic, clk_id, freq);

	dev_err(dmic->dev, "invalid clock direction (%d)\n", dir);
	return -EINVAL;
}