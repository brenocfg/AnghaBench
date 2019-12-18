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

/* Variables and functions */
 int /*<<< orphan*/  AUD_PLL_A1 ; 
 int /*<<< orphan*/  AUD_PLL_A2 ; 
 int /*<<< orphan*/  AUD_PLL_F1 ; 
 int /*<<< orphan*/  AUD_PLL_F2 ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int uniphier_aio_dai_probe (struct snd_soc_dai*) ; 

__attribute__((used)) static int uniphier_aio_ld11_probe(struct snd_soc_dai *dai)
{
	int ret;

	ret = uniphier_aio_dai_probe(dai);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_pll(dai, AUD_PLL_A1, 0, 0, 36864000);
	if (ret < 0)
		return ret;
	ret = snd_soc_dai_set_pll(dai, AUD_PLL_F1, 0, 0, 36864000);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_pll(dai, AUD_PLL_A2, 0, 0, 33868800);
	if (ret < 0)
		return ret;
	ret = snd_soc_dai_set_pll(dai, AUD_PLL_F2, 0, 0, 33868800);
	if (ret < 0)
		return ret;

	return 0;
}