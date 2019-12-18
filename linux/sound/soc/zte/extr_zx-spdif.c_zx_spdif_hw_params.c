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
struct zx_spdif_info {int /*<<< orphan*/  dai_clk; scalar_t__ reg_base; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int addr_width; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S18_3LE 130 
#define  SNDRV_PCM_FORMAT_S20_3LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 scalar_t__ ZX_CTRL ; 
 int ZX_CTRL_DOUBLE_TRACK ; 
 int ZX_CTRL_LEFT_TRACK ; 
 int ZX_CTRL_MODA_16 ; 
 int ZX_CTRL_MODA_18 ; 
 int ZX_CTRL_MODA_20 ; 
 int ZX_CTRL_MODA_24 ; 
 int ZX_CTRL_MODA_MASK ; 
 int ZX_SPDIF_CLK_RAT ; 
 scalar_t__ ZX_VALID_BIT ; 
 int ZX_VALID_DOUBLE_TRACK ; 
 int ZX_VALID_RIGHT_TRACK ; 
 int ZX_VALID_TRACK_MASK ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct zx_spdif_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int readl_relaxed (scalar_t__) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct zx_spdif_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int zx_spdif_chanstats (scalar_t__,int) ; 

__attribute__((used)) static int zx_spdif_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params,
			      struct snd_soc_dai *socdai)
{
	struct zx_spdif_info *zx_spdif = dev_get_drvdata(socdai->dev);
	struct zx_spdif_info *spdif = snd_soc_dai_get_drvdata(socdai);
	struct snd_dmaengine_dai_dma_data *dma_data =
		snd_soc_dai_get_dma_data(socdai, substream);
	u32 val, ch_num, rate;
	int ret;

	dma_data->addr_width = params_width(params) >> 3;

	val = readl_relaxed(zx_spdif->reg_base + ZX_CTRL);
	val &= ~ZX_CTRL_MODA_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		val |= ZX_CTRL_MODA_16;
		break;

	case SNDRV_PCM_FORMAT_S18_3LE:
		val |= ZX_CTRL_MODA_18;
		break;

	case SNDRV_PCM_FORMAT_S20_3LE:
		val |= ZX_CTRL_MODA_20;
		break;

	case SNDRV_PCM_FORMAT_S24_LE:
		val |= ZX_CTRL_MODA_24;
		break;
	default:
		dev_err(socdai->dev, "Format not support!\n");
		return -EINVAL;
	}

	ch_num = params_channels(params);
	if (ch_num == 2)
		val |= ZX_CTRL_DOUBLE_TRACK;
	else
		val |= ZX_CTRL_LEFT_TRACK;
	writel_relaxed(val, zx_spdif->reg_base + ZX_CTRL);

	val = readl_relaxed(zx_spdif->reg_base + ZX_VALID_BIT);
	val &= ~ZX_VALID_TRACK_MASK;
	if (ch_num == 2)
		val |= ZX_VALID_DOUBLE_TRACK;
	else
		val |= ZX_VALID_RIGHT_TRACK;
	writel_relaxed(val, zx_spdif->reg_base + ZX_VALID_BIT);

	rate = params_rate(params);
	ret = zx_spdif_chanstats(zx_spdif->reg_base, rate);
	if (ret)
		return ret;
	return clk_set_rate(spdif->dai_clk, rate * ch_num * ZX_SPDIF_CLK_RAT);
}