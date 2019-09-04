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
typedef  size_t u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct regmap {int dummy; } ;
struct fsl_spdif_priv {int /*<<< orphan*/  coreclk; int /*<<< orphan*/  spbaclk; int /*<<< orphan*/  rxclk; int /*<<< orphan*/ * txclk; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SPDIF_SCR ; 
 size_t SCR_LOW_POWER ; 
 size_t SCR_RXFIFO_AUTOSYNC_MASK ; 
 size_t SCR_RXFIFO_CTL_MASK ; 
 size_t SCR_RXFIFO_CTL_ZERO ; 
 size_t SCR_RXFIFO_FSEL_MASK ; 
 size_t SCR_RXFIFO_OFF ; 
 size_t SCR_RXFIFO_OFF_MASK ; 
 size_t SCR_TXFIFO_AUTOSYNC_MASK ; 
 size_t SCR_TXFIFO_CTRL_MASK ; 
 size_t SCR_TXFIFO_FSEL_MASK ; 
 size_t SCR_TXSEL_MASK ; 
 size_t SCR_USRC_SEL_MASK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 size_t SPDIF_TXRATE_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,size_t,size_t) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spdif_intr_status_clear (struct fsl_spdif_priv*) ; 

__attribute__((used)) static void fsl_spdif_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *cpu_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct regmap *regmap = spdif_priv->regmap;
	u32 scr, mask, i;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		scr = 0;
		mask = SCR_TXFIFO_AUTOSYNC_MASK | SCR_TXFIFO_CTRL_MASK |
			SCR_TXSEL_MASK | SCR_USRC_SEL_MASK |
			SCR_TXFIFO_FSEL_MASK;
		for (i = 0; i < SPDIF_TXRATE_MAX; i++)
			clk_disable_unprepare(spdif_priv->txclk[i]);
	} else {
		scr = SCR_RXFIFO_OFF | SCR_RXFIFO_CTL_ZERO;
		mask = SCR_RXFIFO_FSEL_MASK | SCR_RXFIFO_AUTOSYNC_MASK|
			SCR_RXFIFO_CTL_MASK | SCR_RXFIFO_OFF_MASK;
		clk_disable_unprepare(spdif_priv->rxclk);
	}
	regmap_update_bits(regmap, REG_SPDIF_SCR, mask, scr);

	/* Power down SPDIF module only if tx&rx are both inactive */
	if (!cpu_dai->active) {
		spdif_intr_status_clear(spdif_priv);
		regmap_update_bits(regmap, REG_SPDIF_SCR,
				SCR_LOW_POWER, SCR_LOW_POWER);
		if (!IS_ERR(spdif_priv->spbaclk))
			clk_disable_unprepare(spdif_priv->spbaclk);
		clk_disable_unprepare(spdif_priv->coreclk);
	}
}