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
typedef  int u8 ;
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct regmap {int dummy; } ;
struct fsl_ssi {int baudclk_streams; int i2s_net; scalar_t__ synchronous; scalar_t__ streams; int /*<<< orphan*/  baudclk; struct regmap* regs; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SxCCR (int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SSI_SCR_I2S_MODE_NORMAL ; 
 int /*<<< orphan*/  SSI_SCR_I2S_NET_MASK ; 
 int SSI_SCR_NET ; 
 int SSI_SxCCR_WL (unsigned int) ; 
 int /*<<< orphan*/  SSI_SxCCR_WL_MASK ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 scalar_t__ fsl_ssi_is_i2s_cbm_cfs (struct fsl_ssi*) ; 
 scalar_t__ fsl_ssi_is_i2s_master (struct fsl_ssi*) ; 
 int fsl_ssi_set_bclk (struct snd_pcm_substream*,struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fsl_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_ssi_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *hw_params,
			     struct snd_soc_dai *dai)
{
	bool tx2, tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	struct fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);
	struct regmap *regs = ssi->regs;
	unsigned int channels = params_channels(hw_params);
	unsigned int sample_size = params_width(hw_params);
	u32 wl = SSI_SxCCR_WL(sample_size);
	int ret;

	if (fsl_ssi_is_i2s_master(ssi)) {
		ret = fsl_ssi_set_bclk(substream, dai, hw_params);
		if (ret)
			return ret;

		/* Do not enable the clock if it is already enabled */
		if (!(ssi->baudclk_streams & BIT(substream->stream))) {
			ret = clk_prepare_enable(ssi->baudclk);
			if (ret)
				return ret;

			ssi->baudclk_streams |= BIT(substream->stream);
		}
	}

	/*
	 * SSI is properly configured if it is enabled and running in
	 * the synchronous mode; Note that AC97 mode is an exception
	 * that should set separate configurations for STCCR and SRCCR
	 * despite running in the synchronous mode.
	 */
	if (ssi->streams && ssi->synchronous)
		return 0;

	if (!fsl_ssi_is_ac97(ssi)) {
		/*
		 * Keep the ssi->i2s_net intact while having a local variable
		 * to override settings for special use cases. Otherwise, the
		 * ssi->i2s_net will lose the settings for regular use cases.
		 */
		u8 i2s_net = ssi->i2s_net;

		/* Normal + Network mode to send 16-bit data in 32-bit frames */
		if (fsl_ssi_is_i2s_cbm_cfs(ssi) && sample_size == 16)
			i2s_net = SSI_SCR_I2S_MODE_NORMAL | SSI_SCR_NET;

		/* Use Normal mode to send mono data at 1st slot of 2 slots */
		if (channels == 1)
			i2s_net = SSI_SCR_I2S_MODE_NORMAL;

		regmap_update_bits(regs, REG_SSI_SCR,
				   SSI_SCR_I2S_NET_MASK, i2s_net);
	}

	/* In synchronous mode, the SSI uses STCCR for capture */
	tx2 = tx || ssi->synchronous;
	regmap_update_bits(regs, REG_SSI_SxCCR(tx2), SSI_SxCCR_WL_MASK, wl);

	return 0;
}