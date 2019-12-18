#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct fsl_sai {int slots; int slot_width; int bclk_ratio; int mclk_streams; size_t* mclk_id; int /*<<< orphan*/  regmap; scalar_t__* synchronous; int /*<<< orphan*/  is_slave_mode; scalar_t__ is_lsb_first; int /*<<< orphan*/  is_dsp_mode; int /*<<< orphan*/ * mclk_clk; TYPE_1__* soc_data; } ;
struct TYPE_2__ {unsigned int reg_offset; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int FSL_SAI_CR4_FRSZ (int) ; 
 int FSL_SAI_CR4_FRSZ_MASK ; 
 int FSL_SAI_CR4_SYWD (int) ; 
 int FSL_SAI_CR4_SYWD_MASK ; 
 int FSL_SAI_CR5_FBT (int) ; 
 int FSL_SAI_CR5_FBT_MASK ; 
 int FSL_SAI_CR5_W0W (int) ; 
 int FSL_SAI_CR5_W0W_MASK ; 
 int FSL_SAI_CR5_WNW (int) ; 
 int FSL_SAI_CR5_WNW_MASK ; 
 int /*<<< orphan*/  FSL_SAI_RCR4 (unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_RCR5 (unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_RMR ; 
 int /*<<< orphan*/  FSL_SAI_TCR4 (unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_TCR5 (unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_TMR ; 
 int /*<<< orphan*/  FSL_SAI_xCR4 (int,unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_xCR5 (int,unsigned int) ; 
 int /*<<< orphan*/  FSL_SAI_xMR (int) ; 
 size_t RX ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 size_t TX ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int fsl_sai_set_bclk (struct snd_soc_dai*,int,int) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_sai_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *cpu_dai)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned int ofs = sai->soc_data->reg_offset;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	unsigned int channels = params_channels(params);
	u32 word_width = params_width(params);
	u32 val_cr4 = 0, val_cr5 = 0;
	u32 slots = (channels == 1) ? 2 : channels;
	u32 slot_width = word_width;
	int ret;

	if (sai->slots)
		slots = sai->slots;

	if (sai->slot_width)
		slot_width = sai->slot_width;

	if (!sai->is_slave_mode) {
		if (sai->bclk_ratio)
			ret = fsl_sai_set_bclk(cpu_dai, tx,
					       sai->bclk_ratio *
					       params_rate(params));
		else
			ret = fsl_sai_set_bclk(cpu_dai, tx,
					       slots * slot_width *
					       params_rate(params));
		if (ret)
			return ret;

		/* Do not enable the clock if it is already enabled */
		if (!(sai->mclk_streams & BIT(substream->stream))) {
			ret = clk_prepare_enable(sai->mclk_clk[sai->mclk_id[tx]]);
			if (ret)
				return ret;

			sai->mclk_streams |= BIT(substream->stream);
		}
	}

	if (!sai->is_dsp_mode)
		val_cr4 |= FSL_SAI_CR4_SYWD(slot_width);

	val_cr5 |= FSL_SAI_CR5_WNW(slot_width);
	val_cr5 |= FSL_SAI_CR5_W0W(slot_width);

	if (sai->is_lsb_first)
		val_cr5 |= FSL_SAI_CR5_FBT(0);
	else
		val_cr5 |= FSL_SAI_CR5_FBT(word_width - 1);

	val_cr4 |= FSL_SAI_CR4_FRSZ(slots);

	/*
	 * For SAI master mode, when Tx(Rx) sync with Rx(Tx) clock, Rx(Tx) will
	 * generate bclk and frame clock for Tx(Rx), we should set RCR4(TCR4),
	 * RCR5(TCR5) and RMR(TMR) for playback(capture), or there will be sync
	 * error.
	 */

	if (!sai->is_slave_mode) {
		if (!sai->synchronous[TX] && sai->synchronous[RX] && !tx) {
			regmap_update_bits(sai->regmap, FSL_SAI_TCR4(ofs),
				FSL_SAI_CR4_SYWD_MASK | FSL_SAI_CR4_FRSZ_MASK,
				val_cr4);
			regmap_update_bits(sai->regmap, FSL_SAI_TCR5(ofs),
				FSL_SAI_CR5_WNW_MASK | FSL_SAI_CR5_W0W_MASK |
				FSL_SAI_CR5_FBT_MASK, val_cr5);
			regmap_write(sai->regmap, FSL_SAI_TMR,
				~0UL - ((1 << channels) - 1));
		} else if (!sai->synchronous[RX] && sai->synchronous[TX] && tx) {
			regmap_update_bits(sai->regmap, FSL_SAI_RCR4(ofs),
				FSL_SAI_CR4_SYWD_MASK | FSL_SAI_CR4_FRSZ_MASK,
				val_cr4);
			regmap_update_bits(sai->regmap, FSL_SAI_RCR5(ofs),
				FSL_SAI_CR5_WNW_MASK | FSL_SAI_CR5_W0W_MASK |
				FSL_SAI_CR5_FBT_MASK, val_cr5);
			regmap_write(sai->regmap, FSL_SAI_RMR,
				~0UL - ((1 << channels) - 1));
		}
	}

	regmap_update_bits(sai->regmap, FSL_SAI_xCR4(tx, ofs),
			   FSL_SAI_CR4_SYWD_MASK | FSL_SAI_CR4_FRSZ_MASK,
			   val_cr4);
	regmap_update_bits(sai->regmap, FSL_SAI_xCR5(tx, ofs),
			   FSL_SAI_CR5_WNW_MASK | FSL_SAI_CR5_W0W_MASK |
			   FSL_SAI_CR5_FBT_MASK, val_cr5);
	regmap_write(sai->regmap, FSL_SAI_xMR(tx), ~0UL - ((1 << channels) - 1));

	return 0;
}