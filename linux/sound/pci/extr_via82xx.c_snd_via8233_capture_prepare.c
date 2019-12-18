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
struct viadev {int dummy; } ;
struct via82xx {int /*<<< orphan*/  ac97; int /*<<< orphan*/ * rates; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ format; int channels; int /*<<< orphan*/  rate; struct viadev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  OFFSET_STOP_IDX ; 
 int /*<<< orphan*/  OFS_CAPTURE_FIFO ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int VIA8233_REG_TYPE_16BIT ; 
 int VIA8233_REG_TYPE_STEREO ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIA_REG_CAPTURE_FIFO_ENABLE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct via82xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx*,struct viadev*) ; 
 int /*<<< orphan*/  snd_via82xx_codec_ready (struct via82xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_set_table_ptr (struct via82xx*,struct viadev*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ via_lock_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_via8233_capture_prepare(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (via_lock_rate(&chip->rates[1], runtime->rate) < 0)
		return -EINVAL;
	snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE, runtime->rate);
	snd_via82xx_channel_reset(chip, viadev);
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(VIA_REG_CAPTURE_FIFO_ENABLE, VIADEV_REG(viadev, OFS_CAPTURE_FIFO));
	outl((runtime->format == SNDRV_PCM_FORMAT_S16_LE ? VIA8233_REG_TYPE_16BIT : 0) |
	     (runtime->channels > 1 ? VIA8233_REG_TYPE_STEREO : 0) |
	     0xff000000,    /* STOP index is never reached */
	     VIADEV_REG(viadev, OFFSET_STOP_IDX));
	udelay(20);
	snd_via82xx_codec_ready(chip, 0);
	return 0;
}