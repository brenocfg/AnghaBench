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
struct axg_pdm {int /*<<< orphan*/  dclk; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  axg_pdm_filters_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct axg_pdm* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void axg_pdm_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct axg_pdm *priv = snd_soc_dai_get_drvdata(dai);

	axg_pdm_filters_enable(priv->map, false);
	clk_disable_unprepare(priv->dclk);
}