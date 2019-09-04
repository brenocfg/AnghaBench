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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int format; int rate; int dma_addr; int /*<<< orphan*/  period_size; } ;
struct atmel_ac97c {int opened; scalar_t__ regs; TYPE_1__* pdev; int /*<<< orphan*/  ac97; scalar_t__ capture_period; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 unsigned long AC97C_CH_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long AC97C_CH_MASK (int /*<<< orphan*/ ) ; 
 unsigned long AC97C_CMR_CEM_LITTLE ; 
 unsigned long AC97C_CMR_DMAEN ; 
 unsigned long AC97C_CMR_SIZE_16 ; 
 unsigned long AC97C_CSR_OVRUN ; 
 unsigned long AC97C_MR_VRA ; 
 unsigned long AC97C_SR_CAEVT ; 
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 scalar_t__ ATMEL_PDC_RCR ; 
 scalar_t__ ATMEL_PDC_RNCR ; 
 scalar_t__ ATMEL_PDC_RNPR ; 
 scalar_t__ ATMEL_PDC_RPR ; 
 int /*<<< orphan*/  CAMR ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICA ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  PCM_LEFT ; 
 int /*<<< orphan*/  PCM_RIGHT ; 
#define  SNDRV_PCM_FORMAT_S16_BE 129 
#define  SNDRV_PCM_FORMAT_S16_LE 128 
 unsigned long ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int atmel_ac97c_capture_prepare(struct snd_pcm_substream *substream)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int block_size = frames_to_bytes(runtime, runtime->period_size);
	unsigned long word = ac97c_readl(chip, ICA);
	int retval;

	chip->capture_period = 0;
	word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));

	/* assign channels to AC97C channel A */
	switch (runtime->channels) {
	case 1:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A);
		break;
	case 2:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A)
			| AC97C_CH_ASSIGN(PCM_RIGHT, A);
		break;
	default:
		/* TODO: support more than two channels */
		return -EINVAL;
	}
	ac97c_writel(chip, ICA, word);

	/* configure sample format and size */
	word = ac97c_readl(chip, CAMR);
	if (chip->opened <= 1)
		word = AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;
	else
		word |= AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;

	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S16_BE: /* fall through */
		word &= ~(AC97C_CMR_CEM_LITTLE);
		break;
	default:
		word = ac97c_readl(chip, ICA);
		word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));
		ac97c_writel(chip, ICA, word);
		return -EINVAL;
	}

	/* Enable overrun interrupt on channel A */
	word |= AC97C_CSR_OVRUN;

	ac97c_writel(chip, CAMR, word);

	/* Enable channel A event interrupt */
	word = ac97c_readl(chip, IMR);
	word |= AC97C_SR_CAEVT;
	ac97c_writel(chip, IER, word);

	/* set variable rate if needed */
	if (runtime->rate != 48000) {
		word = ac97c_readl(chip, MR);
		word |= AC97C_MR_VRA;
		ac97c_writel(chip, MR, word);
	} else {
		word = ac97c_readl(chip, MR);
		word &= ~(AC97C_MR_VRA);
		ac97c_writel(chip, MR, word);
	}

	retval = snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE,
			runtime->rate);
	if (retval)
		dev_dbg(&chip->pdev->dev, "could not set rate %d Hz\n",
				runtime->rate);

	/* Initialize and start the PDC */
	writel(runtime->dma_addr, chip->regs + ATMEL_PDC_RPR);
	writel(block_size / 2, chip->regs + ATMEL_PDC_RCR);
	writel(runtime->dma_addr + block_size, chip->regs + ATMEL_PDC_RNPR);
	writel(block_size / 2, chip->regs + ATMEL_PDC_RNCR);

	return retval;
}