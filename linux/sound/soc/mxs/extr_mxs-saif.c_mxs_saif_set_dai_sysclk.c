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
struct mxs_saif {unsigned int mclk; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MXS_SAIF_MCLK 128 
 struct mxs_saif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mxs_saif_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
			int clk_id, unsigned int freq, int dir)
{
	struct mxs_saif *saif = snd_soc_dai_get_drvdata(cpu_dai);

	switch (clk_id) {
	case MXS_SAIF_MCLK:
		saif->mclk = freq;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}