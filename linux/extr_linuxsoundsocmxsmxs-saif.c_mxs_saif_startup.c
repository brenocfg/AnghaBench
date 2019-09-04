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
struct mxs_saif {int /*<<< orphan*/  clk; scalar_t__ base; scalar_t__ fifo_overrun; scalar_t__ fifo_underrun; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SAIF_CTRL_CLKGATE ; 
 int /*<<< orphan*/  BM_SAIF_CTRL_SFTRST ; 
 scalar_t__ MXS_CLR_ADDR ; 
 scalar_t__ SAIF_CTRL ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 struct mxs_saif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mxs_saif_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *cpu_dai)
{
	struct mxs_saif *saif = snd_soc_dai_get_drvdata(cpu_dai);
	int ret;

	/* clear error status to 0 for each re-open */
	saif->fifo_underrun = 0;
	saif->fifo_overrun = 0;

	/* Clear Reset for normal operations */
	__raw_writel(BM_SAIF_CTRL_SFTRST,
		saif->base + SAIF_CTRL + MXS_CLR_ADDR);

	/* clear clock gate */
	__raw_writel(BM_SAIF_CTRL_CLKGATE,
		saif->base + SAIF_CTRL + MXS_CLR_ADDR);

	ret = clk_prepare(saif->clk);
	if (ret)
		return ret;

	return 0;
}