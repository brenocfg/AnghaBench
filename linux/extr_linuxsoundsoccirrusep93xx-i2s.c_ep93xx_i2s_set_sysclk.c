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
struct ep93xx_i2s_info {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_CLOCK_IN ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct ep93xx_i2s_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int ep93xx_i2s_set_sysclk(struct snd_soc_dai *cpu_dai, int clk_id,
				 unsigned int freq, int dir)
{
	struct ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(cpu_dai);

	if (dir == SND_SOC_CLOCK_IN || clk_id != 0)
		return -EINVAL;

	return clk_set_rate(info->mclk, freq);
}