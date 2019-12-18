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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct spdif_mixer_control {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {scalar_t__* txclk_src; scalar_t__* txclk_df; int* sysclk_df; int /*<<< orphan*/ * txrate; int /*<<< orphan*/ * txclk; struct platform_device* pdev; struct regmap* regmap; struct spdif_mixer_control fsl_spdif_control; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEC958_AES3_CON_FS ; 
 unsigned long IEC958_AES3_CON_FS_192000 ; 
 unsigned long IEC958_AES3_CON_FS_32000 ; 
 unsigned long IEC958_AES3_CON_FS_44100 ; 
 unsigned long IEC958_AES3_CON_FS_48000 ; 
 unsigned long IEC958_AES3_CON_FS_96000 ; 
 int /*<<< orphan*/  REG_SPDIF_STC ; 
 size_t SPDIF_TXRATE_192000 ; 
 size_t SPDIF_TXRATE_32000 ; 
 size_t SPDIF_TXRATE_44100 ; 
 size_t SPDIF_TXRATE_48000 ; 
 size_t SPDIF_TXRATE_96000 ; 
 size_t STC_SYSCLK_DF (int) ; 
 size_t STC_SYSCLK_DF_MASK ; 
 size_t STC_TXCLK_ALL_EN ; 
 size_t STC_TXCLK_ALL_EN_MASK ; 
 size_t STC_TXCLK_DF (scalar_t__) ; 
 size_t STC_TXCLK_DF_MASK ; 
 scalar_t__ STC_TXCLK_SPDIF_ROOT ; 
 size_t STC_TXCLK_SRC_MASK ; 
 scalar_t__ STC_TXCLK_SRC_MAX ; 
 size_t STC_TXCLK_SRC_SET (scalar_t__) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,size_t,size_t) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spdif_set_cstatus (struct spdif_mixer_control*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int spdif_set_sample_rate(struct snd_pcm_substream *substream,
				int sample_rate)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	struct regmap *regmap = spdif_priv->regmap;
	struct platform_device *pdev = spdif_priv->pdev;
	unsigned long csfs = 0;
	u32 stc, mask, rate;
	u16 sysclk_df;
	u8 clk, txclk_df;
	int ret;

	switch (sample_rate) {
	case 32000:
		rate = SPDIF_TXRATE_32000;
		csfs = IEC958_AES3_CON_FS_32000;
		break;
	case 44100:
		rate = SPDIF_TXRATE_44100;
		csfs = IEC958_AES3_CON_FS_44100;
		break;
	case 48000:
		rate = SPDIF_TXRATE_48000;
		csfs = IEC958_AES3_CON_FS_48000;
		break;
	case 96000:
		rate = SPDIF_TXRATE_96000;
		csfs = IEC958_AES3_CON_FS_96000;
		break;
	case 192000:
		rate = SPDIF_TXRATE_192000;
		csfs = IEC958_AES3_CON_FS_192000;
		break;
	default:
		dev_err(&pdev->dev, "unsupported sample rate %d\n", sample_rate);
		return -EINVAL;
	}

	clk = spdif_priv->txclk_src[rate];
	if (clk >= STC_TXCLK_SRC_MAX) {
		dev_err(&pdev->dev, "tx clock source is out of range\n");
		return -EINVAL;
	}

	txclk_df = spdif_priv->txclk_df[rate];
	if (txclk_df == 0) {
		dev_err(&pdev->dev, "the txclk_df can't be zero\n");
		return -EINVAL;
	}

	sysclk_df = spdif_priv->sysclk_df[rate];

	/* Don't mess up the clocks from other modules */
	if (clk != STC_TXCLK_SPDIF_ROOT)
		goto clk_set_bypass;

	/* The S/PDIF block needs a clock of 64 * fs * txclk_df */
	ret = clk_set_rate(spdif_priv->txclk[rate],
			   64 * sample_rate * txclk_df);
	if (ret) {
		dev_err(&pdev->dev, "failed to set tx clock rate\n");
		return ret;
	}

clk_set_bypass:
	dev_dbg(&pdev->dev, "expected clock rate = %d\n",
			(64 * sample_rate * txclk_df * sysclk_df));
	dev_dbg(&pdev->dev, "actual clock rate = %ld\n",
			clk_get_rate(spdif_priv->txclk[rate]));

	/* set fs field in consumer channel status */
	spdif_set_cstatus(ctrl, IEC958_AES3_CON_FS, csfs);

	/* select clock source and divisor */
	stc = STC_TXCLK_ALL_EN | STC_TXCLK_SRC_SET(clk) |
	      STC_TXCLK_DF(txclk_df) | STC_SYSCLK_DF(sysclk_df);
	mask = STC_TXCLK_ALL_EN_MASK | STC_TXCLK_SRC_MASK |
	       STC_TXCLK_DF_MASK | STC_SYSCLK_DF_MASK;
	regmap_update_bits(regmap, REG_SPDIF_STC, mask, stc);

	dev_dbg(&pdev->dev, "set sample rate to %dHz for %dHz playback\n",
			spdif_priv->txrate[rate], sample_rate);

	return 0;
}