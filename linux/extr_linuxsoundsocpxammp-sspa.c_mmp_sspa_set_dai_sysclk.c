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
struct sspa_priv {int /*<<< orphan*/  audio_clk; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMP_SSPA_CLK_AUDIO 130 
#define  MMP_SSPA_CLK_PLL 129 
#define  MMP_SSPA_CLK_VCXO 128 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct sspa_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mmp_sspa_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
				    int clk_id, unsigned int freq, int dir)
{
	struct sspa_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	int ret = 0;

	switch (clk_id) {
	case MMP_SSPA_CLK_AUDIO:
		ret = clk_set_rate(priv->audio_clk, freq);
		if (ret)
			return ret;
		break;
	case MMP_SSPA_CLK_PLL:
	case MMP_SSPA_CLK_VCXO:
		/* not support yet */
		return -EINVAL;
	default:
		return -EINVAL;
	}

	return 0;
}