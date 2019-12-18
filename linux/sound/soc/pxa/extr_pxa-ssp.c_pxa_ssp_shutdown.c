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
struct ssp_priv {scalar_t__ extclk; struct ssp_device* ssp; } ;
struct ssp_device {scalar_t__ clk; } ;
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_disable (struct ssp_device*) ; 
 int /*<<< orphan*/  snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct ssp_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_ssp_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *cpu_dai)
{
	struct ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct ssp_device *ssp = priv->ssp;

	if (!cpu_dai->active) {
		pxa_ssp_disable(ssp);
		clk_disable_unprepare(ssp->clk);
	}

	if (priv->extclk)
		clk_disable_unprepare(priv->extclk);

	kfree(snd_soc_dai_get_dma_data(cpu_dai, substream));
	snd_soc_dai_set_dma_data(cpu_dai, substream, NULL);
}