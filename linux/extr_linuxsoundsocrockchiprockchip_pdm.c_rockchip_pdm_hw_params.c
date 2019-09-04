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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rk_pdm_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int EINVAL ; 
 unsigned int PDM_CLK_1280FS ; 
 unsigned int PDM_CLK_2560FS ; 
 unsigned int PDM_CLK_320FS ; 
 unsigned int PDM_CLK_5120FS ; 
 unsigned int PDM_CLK_640FS ; 
 int /*<<< orphan*/  PDM_CLK_CTRL ; 
 unsigned int PDM_CLK_EN ; 
 int /*<<< orphan*/  PDM_CTRL0 ; 
 int /*<<< orphan*/  PDM_DMA_CTRL ; 
 unsigned int PDM_DMA_RDL (int) ; 
 unsigned int PDM_DMA_RDL_MSK ; 
 unsigned int PDM_DS_RATIO_MSK ; 
 unsigned int PDM_HPF_60HZ ; 
 unsigned int PDM_HPF_CF_MSK ; 
 int /*<<< orphan*/  PDM_HPF_CTRL ; 
 unsigned int PDM_HPF_LE ; 
 unsigned int PDM_HPF_RE ; 
 unsigned int PDM_PATH0_EN ; 
 unsigned int PDM_PATH1_EN ; 
 unsigned int PDM_PATH2_EN ; 
 unsigned int PDM_PATH3_EN ; 
 unsigned int PDM_PATH_MSK ; 
 unsigned int PDM_RX_CLR_MASK ; 
 unsigned int PDM_RX_CLR_WR ; 
 unsigned int PDM_RX_MASK ; 
 unsigned int PDM_RX_STOP ; 
 int /*<<< orphan*/  PDM_SYSCONFIG ; 
 unsigned int PDM_VDW (int) ; 
 unsigned int PDM_VDW_MSK ; 
#define  SNDRV_PCM_FORMAT_S16_LE 132 
#define  SNDRV_PCM_FORMAT_S20_3LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int get_pdm_clk (unsigned int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct rk_pdm_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_pdm_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct rk_pdm_dev *pdm = to_info(dai);
	unsigned int val = 0;
	unsigned int clk_rate, clk_div, samplerate;
	int ret;

	samplerate = params_rate(params);
	clk_rate = get_pdm_clk(samplerate);
	if (!clk_rate)
		return -EINVAL;

	ret = clk_set_rate(pdm->clk, clk_rate);
	if (ret)
		return -EINVAL;

	clk_div = DIV_ROUND_CLOSEST(clk_rate, samplerate);

	switch (clk_div) {
	case 320:
		val = PDM_CLK_320FS;
		break;
	case 640:
		val = PDM_CLK_640FS;
		break;
	case 1280:
		val = PDM_CLK_1280FS;
		break;
	case 2560:
		val = PDM_CLK_2560FS;
		break;
	case 5120:
		val = PDM_CLK_5120FS;
		break;
	default:
		dev_err(pdm->dev, "unsupported div: %d\n", clk_div);
		return -EINVAL;
	}

	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_DS_RATIO_MSK, val);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_CF_MSK, PDM_HPF_60HZ);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_LE | PDM_HPF_RE, PDM_HPF_LE | PDM_HPF_RE);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_CLK_EN, PDM_CLK_EN);

	val = 0;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S8:
		val |= PDM_VDW(8);
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		val |= PDM_VDW(16);
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		val |= PDM_VDW(20);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		val |= PDM_VDW(24);
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		val |= PDM_VDW(32);
		break;
	default:
		return -EINVAL;
	}

	switch (params_channels(params)) {
	case 8:
		val |= PDM_PATH3_EN;
		/* fallthrough */
	case 6:
		val |= PDM_PATH2_EN;
		/* fallthrough */
	case 4:
		val |= PDM_PATH1_EN;
		/* fallthrough */
	case 2:
		val |= PDM_PATH0_EN;
		break;
	default:
		dev_err(pdm->dev, "invalid channel: %d\n",
			params_channels(params));
		return -EINVAL;
	}

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		regmap_update_bits(pdm->regmap, PDM_CTRL0,
				   PDM_PATH_MSK | PDM_VDW_MSK,
				   val);
		regmap_update_bits(pdm->regmap, PDM_DMA_CTRL, PDM_DMA_RDL_MSK,
				   PDM_DMA_RDL(16));
		regmap_update_bits(pdm->regmap, PDM_SYSCONFIG,
				   PDM_RX_MASK | PDM_RX_CLR_MASK,
				   PDM_RX_STOP | PDM_RX_CLR_WR);
	}

	return 0;
}