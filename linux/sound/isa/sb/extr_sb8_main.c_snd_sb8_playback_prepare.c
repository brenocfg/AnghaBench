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
struct snd_sb {int hardware; int mode; unsigned int playback_format; int dma16; int dma8; unsigned int p_dma_size; unsigned int p_period_size; unsigned int force_mode16; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mixer_lock; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; unsigned int rate; int* dma_area; int rate_den; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int DMA_AUTOINIT ; 
 int DMA_MODE_WRITE ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int SB8_RATE (int) ; 
 unsigned int SB_DSP_BLOCK_SIZE ; 
 unsigned int SB_DSP_DMA8_EXIT ; 
 void* SB_DSP_HI_OUTPUT_AUTO ; 
 void* SB_DSP_LO_OUTPUT_AUTO ; 
 unsigned char SB_DSP_MONO_16BIT ; 
 unsigned char SB_DSP_MONO_8BIT ; 
 unsigned int SB_DSP_OUTPUT ; 
 int /*<<< orphan*/  SB_DSP_PLAYBACK_FILT ; 
 unsigned int SB_DSP_SAMPLE_RATE ; 
 unsigned int SB_DSP_SPEAKER_ON ; 
 unsigned char SB_DSP_STEREO_16BIT ; 
 unsigned char SB_DSP_STEREO_8BIT ; 
 int /*<<< orphan*/  SB_DSP_STEREO_SW ; 
#define  SB_HW_10 132 
#define  SB_HW_20 131 
#define  SB_HW_201 130 
#define  SB_HW_JAZZ16 129 
#define  SB_HW_PRO 128 
 int SB_MODE_CAPTURE_16 ; 
 int SB_MODE_PLAYBACK_16 ; 
 int SB_MODE_PLAYBACK_8 ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_dma_program (int,int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned int) ; 
 unsigned int snd_sbmixer_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8_playback_prepare(struct snd_pcm_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int mixreg, rate, size, count;
	unsigned char format;
	unsigned char stereo = runtime->channels > 1;
	int dma;

	rate = runtime->rate;
	switch (chip->hardware) {
	case SB_HW_JAZZ16:
		if (runtime->format == SNDRV_PCM_FORMAT_S16_LE) {
			if (chip->mode & SB_MODE_CAPTURE_16)
				return -EBUSY;
			else
				chip->mode |= SB_MODE_PLAYBACK_16;
		}
		chip->playback_format = SB_DSP_LO_OUTPUT_AUTO;
		break;
	case SB_HW_PRO:
		if (runtime->channels > 1) {
			if (snd_BUG_ON(rate != SB8_RATE(11025) &&
				       rate != SB8_RATE(22050)))
				return -EINVAL;
			chip->playback_format = SB_DSP_HI_OUTPUT_AUTO;
			break;
		}
		/* fall through */
	case SB_HW_201:
		if (rate > 23000) {
			chip->playback_format = SB_DSP_HI_OUTPUT_AUTO;
			break;
		}
		/* fall through */
	case SB_HW_20:
		chip->playback_format = SB_DSP_LO_OUTPUT_AUTO;
		break;
	case SB_HW_10:
		chip->playback_format = SB_DSP_OUTPUT;
		break;
	default:
		return -EINVAL;
	}
	if (chip->mode & SB_MODE_PLAYBACK_16) {
		format = stereo ? SB_DSP_STEREO_16BIT : SB_DSP_MONO_16BIT;
		dma = chip->dma16;
	} else {
		format = stereo ? SB_DSP_STEREO_8BIT : SB_DSP_MONO_8BIT;
		chip->mode |= SB_MODE_PLAYBACK_8;
		dma = chip->dma8;
	}
	size = chip->p_dma_size = snd_pcm_lib_buffer_bytes(substream);
	count = chip->p_period_size = snd_pcm_lib_period_bytes(substream);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_sbdsp_command(chip, SB_DSP_SPEAKER_ON);
	if (chip->hardware == SB_HW_JAZZ16)
		snd_sbdsp_command(chip, format);
	else if (stereo) {
		/* set playback stereo mode */
		spin_lock(&chip->mixer_lock);
		mixreg = snd_sbmixer_read(chip, SB_DSP_STEREO_SW);
		snd_sbmixer_write(chip, SB_DSP_STEREO_SW, mixreg | 0x02);
		spin_unlock(&chip->mixer_lock);

		/* Soundblaster hardware programming reference guide, 3-23 */
		snd_sbdsp_command(chip, SB_DSP_DMA8_EXIT);
		runtime->dma_area[0] = 0x80;
		snd_dma_program(dma, runtime->dma_addr, 1, DMA_MODE_WRITE);
		/* force interrupt */
		snd_sbdsp_command(chip, SB_DSP_OUTPUT);
		snd_sbdsp_command(chip, 0);
		snd_sbdsp_command(chip, 0);
	}
	snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE);
	if (stereo) {
		snd_sbdsp_command(chip, 256 - runtime->rate_den / 2);
		spin_lock(&chip->mixer_lock);
		/* save output filter status and turn it off */
		mixreg = snd_sbmixer_read(chip, SB_DSP_PLAYBACK_FILT);
		snd_sbmixer_write(chip, SB_DSP_PLAYBACK_FILT, mixreg | 0x20);
		spin_unlock(&chip->mixer_lock);
		/* just use force_mode16 for temporary storate... */
		chip->force_mode16 = mixreg;
	} else {
		snd_sbdsp_command(chip, 256 - runtime->rate_den);
	}
	if (chip->playback_format != SB_DSP_OUTPUT) {
		if (chip->mode & SB_MODE_PLAYBACK_16)
			count /= 2;
		count--;
		snd_sbdsp_command(chip, SB_DSP_BLOCK_SIZE);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_dma_program(dma, runtime->dma_addr,
			size, DMA_MODE_WRITE | DMA_AUTOINIT);
	return 0;
}