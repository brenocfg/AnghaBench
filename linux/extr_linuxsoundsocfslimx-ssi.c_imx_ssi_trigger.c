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
struct imx_ssi {int flags; scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMX_SSI_DMA ; 
 int IMX_SSI_USE_AC97 ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ SSI_SCR ; 
 unsigned int SSI_SCR_RE ; 
 unsigned int SSI_SCR_SSIEN ; 
 unsigned int SSI_SCR_TE ; 
 scalar_t__ SSI_SIER ; 
 unsigned int SSI_SIER_RDMAE ; 
 unsigned int SSI_SIER_RFF0_EN ; 
 unsigned int SSI_SIER_RIE ; 
 unsigned int SSI_SIER_TDMAE ; 
 unsigned int SSI_SIER_TFE0_EN ; 
 unsigned int SSI_SIER_TIE ; 
 unsigned int readl (scalar_t__) ; 
 struct imx_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_trigger(struct snd_pcm_substream *substream, int cmd,
		struct snd_soc_dai *dai)
{
	struct imx_ssi *ssi = snd_soc_dai_get_drvdata(dai);
	unsigned int sier_bits, sier;
	unsigned int scr;

	scr = readl(ssi->base + SSI_SCR);
	sier = readl(ssi->base + SSI_SIER);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (ssi->flags & IMX_SSI_DMA)
			sier_bits = SSI_SIER_TDMAE;
		else
			sier_bits = SSI_SIER_TIE | SSI_SIER_TFE0_EN;
	} else {
		if (ssi->flags & IMX_SSI_DMA)
			sier_bits = SSI_SIER_RDMAE;
		else
			sier_bits = SSI_SIER_RIE | SSI_SIER_RFF0_EN;
	}

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			scr |= SSI_SCR_TE;
		else
			scr |= SSI_SCR_RE;
		sier |= sier_bits;

		scr |= SSI_SCR_SSIEN;

		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			scr &= ~SSI_SCR_TE;
		else
			scr &= ~SSI_SCR_RE;
		sier &= ~sier_bits;

		if (!(scr & (SSI_SCR_TE | SSI_SCR_RE)))
			scr &= ~SSI_SCR_SSIEN;

		break;
	default:
		return -EINVAL;
	}

	if (!(ssi->flags & IMX_SSI_USE_AC97))
		/* rx/tx are always enabled to access ac97 registers */
		writel(scr, ssi->base + SSI_SCR);

	writel(sier, ssi->base + SSI_SIER);

	return 0;
}