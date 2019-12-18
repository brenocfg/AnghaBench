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
struct snd_pcm_substream {int dummy; } ;
struct axg_spdifin {int /*<<< orphan*/  refclk; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIFIN_CTRL0 ; 
 int /*<<< orphan*/  SPDIFIN_CTRL0_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axg_spdifin* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void axg_spdifin_shutdown(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct axg_spdifin *priv = snd_soc_dai_get_drvdata(dai);

	regmap_update_bits(priv->map, SPDIFIN_CTRL0, SPDIFIN_CTRL0_EN, 0);
	clk_disable_unprepare(priv->refclk);
}