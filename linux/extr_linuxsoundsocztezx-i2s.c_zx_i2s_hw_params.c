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
struct zx_i2s_info {int /*<<< orphan*/  dai_wclk; scalar_t__ master; scalar_t__ reg_base; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {unsigned int addr_width; } ;

/* Variables and functions */
 unsigned int CLK_RAT ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 unsigned long ZX_I2S_TIMING_CHN (unsigned int) ; 
 unsigned long ZX_I2S_TIMING_CHN_MASK ; 
 scalar_t__ ZX_I2S_TIMING_CTRL ; 
 unsigned long ZX_I2S_TIMING_DATA_SIZE (unsigned int) ; 
 unsigned long ZX_I2S_TIMING_DATA_SIZE_MASK ; 
 unsigned long ZX_I2S_TIMING_LANE (unsigned int) ; 
 unsigned long ZX_I2S_TIMING_LANE_MASK ; 
 unsigned long ZX_I2S_TIMING_TSCFG (unsigned long) ; 
 unsigned long ZX_I2S_TIMING_TSCFG_MASK ; 
 unsigned long ZX_I2S_TIMING_TS_WIDTH (unsigned int) ; 
 unsigned long ZX_I2S_TIMING_TS_WIDTH_MASK ; 
 unsigned int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct zx_i2s_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int zx_i2s_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *socdai)
{
	struct zx_i2s_info *i2s = snd_soc_dai_get_drvdata(socdai);
	struct snd_dmaengine_dai_dma_data *dma_data;
	unsigned int lane, ch_num, len, ret = 0;
	unsigned int ts_width = 32;
	unsigned long val;
	unsigned long chn_cfg;

	dma_data = snd_soc_dai_get_dma_data(socdai, substream);
	dma_data->addr_width = ts_width >> 3;

	val = readl_relaxed(i2s->reg_base + ZX_I2S_TIMING_CTRL);
	val &= ~(ZX_I2S_TIMING_TS_WIDTH_MASK | ZX_I2S_TIMING_DATA_SIZE_MASK |
		ZX_I2S_TIMING_LANE_MASK | ZX_I2S_TIMING_CHN_MASK |
		ZX_I2S_TIMING_TSCFG_MASK);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		len = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		len = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		len = 32;
		break;
	default:
		dev_err(socdai->dev, "Unknown data format\n");
		return -EINVAL;
	}
	val |= ZX_I2S_TIMING_TS_WIDTH(ts_width) | ZX_I2S_TIMING_DATA_SIZE(len);

	ch_num = params_channels(params);
	switch (ch_num) {
	case 1:
		lane = 1;
		chn_cfg = 2;
		break;
	case 2:
	case 4:
	case 6:
	case 8:
		lane = ch_num / 2;
		chn_cfg = 3;
		break;
	default:
		dev_err(socdai->dev, "Not support channel num %d\n", ch_num);
		return -EINVAL;
	}
	val |= ZX_I2S_TIMING_LANE(lane);
	val |= ZX_I2S_TIMING_TSCFG(chn_cfg);
	val |= ZX_I2S_TIMING_CHN(ch_num);
	writel_relaxed(val, i2s->reg_base + ZX_I2S_TIMING_CTRL);

	if (i2s->master)
		ret = clk_set_rate(i2s->dai_wclk,
				params_rate(params) * ch_num * CLK_RAT);

	return ret;
}