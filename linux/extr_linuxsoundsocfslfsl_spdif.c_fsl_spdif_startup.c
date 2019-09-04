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
typedef  int u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {int /*<<< orphan*/  coreclk; int /*<<< orphan*/  spbaclk; int /*<<< orphan*/ * txclk; int /*<<< orphan*/  rxclk; struct regmap* regmap; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SPDIF_SCR ; 
 int /*<<< orphan*/  REG_SPDIF_SIE ; 
 int SCR_LOW_POWER ; 
 int SCR_RXFIFO_AUTOSYNC ; 
 int SCR_RXFIFO_AUTOSYNC_MASK ; 
 int SCR_RXFIFO_CTL_MASK ; 
 int SCR_RXFIFO_FSEL_IF8 ; 
 int SCR_RXFIFO_FSEL_MASK ; 
 int SCR_RXFIFO_OFF_MASK ; 
 int SCR_TXFIFO_AUTOSYNC ; 
 int SCR_TXFIFO_AUTOSYNC_MASK ; 
 int SCR_TXFIFO_CTRL_MASK ; 
 int SCR_TXFIFO_CTRL_NORMAL ; 
 int SCR_TXFIFO_FSEL_IF8 ; 
 int SCR_TXFIFO_FSEL_MASK ; 
 int SCR_TXSEL_MASK ; 
 int SCR_TXSEL_NORMAL ; 
 int SCR_USRC_SEL_CHIP ; 
 int SCR_USRC_SEL_MASK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SPDIF_TXRATE_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int spdif_softreset (struct fsl_spdif_priv*) ; 

__attribute__((used)) static int fsl_spdif_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *cpu_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct platform_device *pdev = spdif_priv->pdev;
	struct regmap *regmap = spdif_priv->regmap;
	u32 scr, mask;
	int i;
	int ret;

	/* Reset module and interrupts only for first initialization */
	if (!cpu_dai->active) {
		ret = clk_prepare_enable(spdif_priv->coreclk);
		if (ret) {
			dev_err(&pdev->dev, "failed to enable core clock\n");
			return ret;
		}

		if (!IS_ERR(spdif_priv->spbaclk)) {
			ret = clk_prepare_enable(spdif_priv->spbaclk);
			if (ret) {
				dev_err(&pdev->dev, "failed to enable spba clock\n");
				goto err_spbaclk;
			}
		}

		ret = spdif_softreset(spdif_priv);
		if (ret) {
			dev_err(&pdev->dev, "failed to soft reset\n");
			goto err;
		}

		/* Disable all the interrupts */
		regmap_update_bits(regmap, REG_SPDIF_SIE, 0xffffff, 0);
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		scr = SCR_TXFIFO_AUTOSYNC | SCR_TXFIFO_CTRL_NORMAL |
			SCR_TXSEL_NORMAL | SCR_USRC_SEL_CHIP |
			SCR_TXFIFO_FSEL_IF8;
		mask = SCR_TXFIFO_AUTOSYNC_MASK | SCR_TXFIFO_CTRL_MASK |
			SCR_TXSEL_MASK | SCR_USRC_SEL_MASK |
			SCR_TXFIFO_FSEL_MASK;
		for (i = 0; i < SPDIF_TXRATE_MAX; i++) {
			ret = clk_prepare_enable(spdif_priv->txclk[i]);
			if (ret)
				goto disable_txclk;
		}
	} else {
		scr = SCR_RXFIFO_FSEL_IF8 | SCR_RXFIFO_AUTOSYNC;
		mask = SCR_RXFIFO_FSEL_MASK | SCR_RXFIFO_AUTOSYNC_MASK|
			SCR_RXFIFO_CTL_MASK | SCR_RXFIFO_OFF_MASK;
		ret = clk_prepare_enable(spdif_priv->rxclk);
		if (ret)
			goto err;
	}
	regmap_update_bits(regmap, REG_SPDIF_SCR, mask, scr);

	/* Power up SPDIF module */
	regmap_update_bits(regmap, REG_SPDIF_SCR, SCR_LOW_POWER, 0);

	return 0;

disable_txclk:
	for (i--; i >= 0; i--)
		clk_disable_unprepare(spdif_priv->txclk[i]);
err:
	if (!IS_ERR(spdif_priv->spbaclk))
		clk_disable_unprepare(spdif_priv->spbaclk);
err_spbaclk:
	clk_disable_unprepare(spdif_priv->coreclk);

	return ret;
}