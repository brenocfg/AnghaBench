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
typedef  int u16 ;
struct snd_pdacf {int chip_status; int pcm_little; int pcm_swab; int pcm_xor; int pcm_sample; int pcm_frame; int /*<<< orphan*/  pcm_area; int /*<<< orphan*/  pcm_period; int /*<<< orphan*/  pcm_size; int /*<<< orphan*/  ak4117; int /*<<< orphan*/  pcm_channels; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int format; int /*<<< orphan*/  dma_area; int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int AK4117_DIF0 ; 
 int AK4117_DIF1 ; 
 int AK4117_DIF2 ; 
 int AK4117_DIF_16R ; 
 int AK4117_DIF_24R ; 
 int /*<<< orphan*/  AK4117_REG_IO ; 
 int EBUSY ; 
 int EIO ; 
 int PDAUDIOCF_DATAFMT0 ; 
 int PDAUDIOCF_DATAFMT1 ; 
 int PDAUDIOCF_IRQLVLEN0 ; 
 int PDAUDIOCF_IRQLVLEN1 ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_IER ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_SCR ; 
 int PDAUDIOCF_STAT_IS_STALE ; 
#define  SNDRV_PCM_FORMAT_S16_BE 131 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_3BE 129 
#define  SNDRV_PCM_FORMAT_S24_3LE 128 
 scalar_t__ pdacf_pcm_clear_sram (struct snd_pdacf*) ; 
 int pdacf_reg_read (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdacf_reg_write (struct snd_pdacf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ak4117_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ snd_pcm_format_big_endian (int) ; 
 scalar_t__ snd_pcm_format_little_endian (int) ; 
 scalar_t__ snd_pcm_format_unsigned (int) ; 
 struct snd_pdacf* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pdacf_pcm_prepare(struct snd_pcm_substream *subs)
{
	struct snd_pdacf *chip = snd_pcm_substream_chip(subs);
	struct snd_pcm_runtime *runtime = subs->runtime;
	u16 val, nval, aval;

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		return -EBUSY;

	chip->pcm_channels = runtime->channels;

	chip->pcm_little = snd_pcm_format_little_endian(runtime->format) > 0;
#ifdef SNDRV_LITTLE_ENDIAN
	chip->pcm_swab = snd_pcm_format_big_endian(runtime->format) > 0;
#else
	chip->pcm_swab = chip->pcm_little;
#endif

	if (snd_pcm_format_unsigned(runtime->format))
		chip->pcm_xor = 0x80008000;

	if (pdacf_pcm_clear_sram(chip) < 0)
		return -EIO;
	
	val = nval = pdacf_reg_read(chip, PDAUDIOCF_REG_SCR);
	nval &= ~(PDAUDIOCF_DATAFMT0|PDAUDIOCF_DATAFMT1);
	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
	case SNDRV_PCM_FORMAT_S16_BE:
		break;
	default: /* 24-bit */
		nval |= PDAUDIOCF_DATAFMT0 | PDAUDIOCF_DATAFMT1;
		break;
	}
	aval = 0;
	chip->pcm_sample = 4;
	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
	case SNDRV_PCM_FORMAT_S16_BE:
		aval = AK4117_DIF_16R;
		chip->pcm_frame = 2;
		chip->pcm_sample = 2;
		break;
	case SNDRV_PCM_FORMAT_S24_3LE:
	case SNDRV_PCM_FORMAT_S24_3BE:
		chip->pcm_sample = 3;
		/* fall through */
	default: /* 24-bit */
		aval = AK4117_DIF_24R;
		chip->pcm_frame = 3;
		chip->pcm_xor &= 0xffff0000;
		break;
	}

	if (val != nval) {
		snd_ak4117_reg_write(chip->ak4117, AK4117_REG_IO, AK4117_DIF2|AK4117_DIF1|AK4117_DIF0, aval);
		pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, nval);
	}

	val = pdacf_reg_read(chip,  PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQLVLEN1);
	val |= PDAUDIOCF_IRQLVLEN0;
	pdacf_reg_write(chip, PDAUDIOCF_REG_IER, val);

	chip->pcm_size = runtime->buffer_size;
	chip->pcm_period = runtime->period_size;
	chip->pcm_area = runtime->dma_area;

	return 0;
}