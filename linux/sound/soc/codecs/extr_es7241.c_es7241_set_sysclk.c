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
struct es7241_data {unsigned int mclk; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int SND_SOC_CLOCK_IN ; 
 struct es7241_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int es7241_set_sysclk(struct snd_soc_dai *dai, int clk_id,
			     unsigned int freq, int dir)
{
	struct es7241_data *priv = snd_soc_dai_get_drvdata(dai);

	if (dir == SND_SOC_CLOCK_IN && clk_id == 0) {
		priv->mclk = freq;
		return 0;
	}

	return -ENOTSUPP;
}