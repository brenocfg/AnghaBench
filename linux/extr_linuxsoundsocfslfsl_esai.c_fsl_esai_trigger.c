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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct fsl_esai {int /*<<< orphan*/  regmap; int /*<<< orphan*/  rx_mask; int /*<<< orphan*/  tx_mask; int /*<<< orphan*/  slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ESAI_xCR_RE (int /*<<< orphan*/ ) ; 
 int ESAI_xCR_RE_MASK ; 
 int ESAI_xCR_TE (int /*<<< orphan*/ ) ; 
 int ESAI_xCR_TE_MASK ; 
 int ESAI_xFCR_xFEN ; 
 int ESAI_xFCR_xFEN_MASK ; 
 int ESAI_xFCR_xFR ; 
 int ESAI_xSMA_xS (int /*<<< orphan*/ ) ; 
 int ESAI_xSMA_xS_MASK ; 
 int ESAI_xSMB_xS (int /*<<< orphan*/ ) ; 
 int ESAI_xSMB_xS_MASK ; 
 int /*<<< orphan*/  REG_ESAI_ETDR ; 
 int /*<<< orphan*/  REG_ESAI_xCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xFCR (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMA (int) ; 
 int /*<<< orphan*/  REG_ESAI_xSMB (int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_trigger(struct snd_pcm_substream *substream, int cmd,
			    struct snd_soc_dai *dai)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u8 i, channels = substream->runtime->channels;
	u32 pins = DIV_ROUND_UP(channels, esai_priv->slots);
	u32 mask;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
				   ESAI_xFCR_xFEN_MASK, ESAI_xFCR_xFEN);

		/* Write initial words reqiured by ESAI as normal procedure */
		for (i = 0; tx && i < channels; i++)
			regmap_write(esai_priv->regmap, REG_ESAI_ETDR, 0x0);

		/*
		 * When set the TE/RE in the end of enablement flow, there
		 * will be channel swap issue for multi data line case.
		 * In order to workaround this issue, we switch the bit
		 * enablement sequence to below sequence
		 * 1) clear the xSMB & xSMA: which is done in probe and
		 *                           stop state.
		 * 2) set TE/RE
		 * 3) set xSMB
		 * 4) set xSMA:  xSMA is the last one in this flow, which
		 *               will trigger esai to start.
		 */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
				   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK,
				   tx ? ESAI_xCR_TE(pins) : ESAI_xCR_RE(pins));
		mask = tx ? esai_priv->tx_mask : esai_priv->rx_mask;

		regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
				   ESAI_xSMB_xS_MASK, ESAI_xSMB_xS(mask));
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
				   ESAI_xSMA_xS_MASK, ESAI_xSMA_xS(mask));

		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
				   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK, 0);
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
				   ESAI_xSMA_xS_MASK, 0);
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
				   ESAI_xSMB_xS_MASK, 0);

		/* Disable and reset FIFO */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
				   ESAI_xFCR_xFR | ESAI_xFCR_xFEN, ESAI_xFCR_xFR);
		regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
				   ESAI_xFCR_xFR, 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}