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
struct wm8974_priv {int mclk; int fs; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8974_MCLKDIV ; 
 struct wm8974_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int wm8974_get_mclkdiv (int,unsigned int,int*) ; 
 int /*<<< orphan*/  wm8974_set_dai_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8974_set_dai_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm8974_update_clocks(struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8974_priv *priv = snd_soc_component_get_drvdata(component);
	unsigned int fs256;
	unsigned int fpll = 0;
	unsigned int f;
	int mclkdiv;

	if (!priv->mclk || !priv->fs)
		return 0;

	fs256 = 256 * priv->fs;

	f = wm8974_get_mclkdiv(priv->mclk, fs256, &mclkdiv);

	if (f != priv->mclk) {
		/* The PLL performs best around 90MHz */
		fpll = wm8974_get_mclkdiv(22500000, fs256, &mclkdiv);
	}

	wm8974_set_dai_pll(dai, 0, 0, priv->mclk, fpll);
	wm8974_set_dai_clkdiv(dai, WM8974_MCLKDIV, mclkdiv);

	return 0;
}