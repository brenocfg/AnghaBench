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
struct rk_pdm_dev {scalar_t__ version; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDM_CLK_CTRL ; 
 unsigned int PDM_CLK_EN ; 
 unsigned int PDM_CLK_FD_RATIO_35 ; 
 unsigned int PDM_CLK_FD_RATIO_40 ; 
 unsigned int PDM_CLK_FD_RATIO_MSK ; 
 int /*<<< orphan*/  PDM_CTRL0 ; 
 int /*<<< orphan*/  PDM_CTRL1 ; 
 int /*<<< orphan*/  PDM_DMA_CTRL ; 
 unsigned int PDM_DMA_RDL (int) ; 
 unsigned int PDM_DMA_RDL_MSK ; 
 unsigned int PDM_DS_RATIO_MSK ; 
 int PDM_FD_DENOMINATOR_MSK ; 
 unsigned long PDM_FD_DENOMINATOR_SFT ; 
 int PDM_FD_NUMERATOR_MSK ; 
 unsigned long PDM_FD_NUMERATOR_SFT ; 
 unsigned int PDM_HPF_60HZ ; 
 unsigned int PDM_HPF_CF_MSK ; 
 int /*<<< orphan*/  PDM_HPF_CTRL ; 
 unsigned int PDM_HPF_LE ; 
 unsigned int PDM_HPF_RE ; 
 unsigned int PDM_MODE_LJ ; 
 unsigned int PDM_MODE_MSK ; 
 unsigned int PDM_PATH0_EN ; 
 unsigned int PDM_PATH1_EN ; 
 unsigned int PDM_PATH2_EN ; 
 unsigned int PDM_PATH3_EN ; 
 unsigned int PDM_PATH_MSK ; 
 unsigned int PDM_VDW (int) ; 
 unsigned int PDM_VDW_MSK ; 
 scalar_t__ RK_PDM_RK3229 ; 
 scalar_t__ RK_PDM_RK3308 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 132 
#define  SNDRV_PCM_FORMAT_S20_3LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int get_pdm_clk (struct rk_pdm_dev*,unsigned int,unsigned int*,unsigned int*) ; 
 unsigned int get_pdm_ds_ratio (unsigned int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  rational_best_approximation (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pdm_rxctrl (struct rk_pdm_dev*,int /*<<< orphan*/ ) ; 
 struct rk_pdm_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_pdm_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct rk_pdm_dev *pdm = to_info(dai);
	unsigned int val = 0;
	unsigned int clk_rate, clk_div, samplerate;
	unsigned int clk_src, clk_out = 0;
	unsigned long m, n;
	bool change;
	int ret;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return 0;

	samplerate = params_rate(params);
	clk_rate = get_pdm_clk(pdm, samplerate, &clk_src, &clk_out);
	if (!clk_rate)
		return -EINVAL;

	ret = clk_set_rate(pdm->clk, clk_src);
	if (ret)
		return -EINVAL;

	if (pdm->version == RK_PDM_RK3308) {
		rational_best_approximation(clk_out, clk_src,
					    GENMASK(16 - 1, 0),
					    GENMASK(16 - 1, 0),
					    &m, &n);

		val = (m << PDM_FD_NUMERATOR_SFT) |
			(n << PDM_FD_DENOMINATOR_SFT);
		regmap_update_bits_check(pdm->regmap, PDM_CTRL1,
					 PDM_FD_NUMERATOR_MSK |
					 PDM_FD_DENOMINATOR_MSK,
					 val, &change);
		if (change) {
			reset_control_assert(pdm->reset);
			reset_control_deassert(pdm->reset);
			rockchip_pdm_rxctrl(pdm, 0);
		}
		clk_div = n / m;
		if (clk_div >= 40)
			val = PDM_CLK_FD_RATIO_40;
		else if (clk_div <= 35)
			val = PDM_CLK_FD_RATIO_35;
		else
			return -EINVAL;
		regmap_update_bits(pdm->regmap, PDM_CLK_CTRL,
				   PDM_CLK_FD_RATIO_MSK,
				   val);
	}
	val = get_pdm_ds_ratio(samplerate);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_DS_RATIO_MSK, val);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_CF_MSK, PDM_HPF_60HZ);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_LE | PDM_HPF_RE, PDM_HPF_LE | PDM_HPF_RE);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_CLK_EN, PDM_CLK_EN);
	if (pdm->version != RK_PDM_RK3229)
		regmap_update_bits(pdm->regmap, PDM_CTRL0,
				   PDM_MODE_MSK, PDM_MODE_LJ);

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

	regmap_update_bits(pdm->regmap, PDM_CTRL0,
			   PDM_PATH_MSK | PDM_VDW_MSK,
			   val);
	/* all channels share the single FIFO */
	regmap_update_bits(pdm->regmap, PDM_DMA_CTRL, PDM_DMA_RDL_MSK,
			   PDM_DMA_RDL(8 * params_channels(params)));

	return 0;
}