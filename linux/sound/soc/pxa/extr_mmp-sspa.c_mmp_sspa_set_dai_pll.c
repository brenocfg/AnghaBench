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
struct sspa_priv {TYPE_1__* sspa; int /*<<< orphan*/  sysclk; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENODEV ; 
#define  MMP_SSPA_CLK 129 
#define  MMP_SYSCLK 128 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct sspa_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mmp_sspa_set_dai_pll(struct snd_soc_dai *cpu_dai, int pll_id,
				 int source, unsigned int freq_in,
				 unsigned int freq_out)
{
	struct sspa_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	int ret = 0;

	switch (pll_id) {
	case MMP_SYSCLK:
		ret = clk_set_rate(priv->sysclk, freq_out);
		if (ret)
			return ret;
		break;
	case MMP_SSPA_CLK:
		ret = clk_set_rate(priv->sspa->clk, freq_out);
		if (ret)
			return ret;
		break;
	default:
		return -ENODEV;
	}

	return 0;
}