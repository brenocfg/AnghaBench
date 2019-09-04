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
struct snd_sb {int playback_format; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  rate; } ;
struct TYPE_2__ {unsigned int dsp_cmd; unsigned int format; unsigned int dma_off; } ;

/* Variables and functions */
 int ALS4000_FORMAT_16BIT ; 
 TYPE_1__ playback_cmd (struct snd_sb*) ; 
 int snd_als4000_get_format (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_als4000_set_playback_dma (struct snd_sb*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  snd_als4000_set_rate (struct snd_sb*,int /*<<< orphan*/ ) ; 
 unsigned long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als4000_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long size;
	unsigned count;

	chip->playback_format = snd_als4000_get_format(runtime);
	
	size = snd_pcm_lib_buffer_bytes(substream);
	count = snd_pcm_lib_period_bytes(substream);
	
	if (chip->playback_format & ALS4000_FORMAT_16BIT)
		count >>= 1;
	count--;
	
	/* FIXME: from second playback on, there's a lot more clicks and pops
	 * involved here than on first playback. Fiddling with
	 * tons of different settings didn't help (DMA, speaker on/off,
	 * reordering, ...). Something seems to get enabled on playback
	 * that I haven't found out how to disable again, which then causes
	 * the switching pops to reach the speakers the next time here. */
	spin_lock_irq(&chip->reg_lock);
	snd_als4000_set_rate(chip, runtime->rate);
	snd_als4000_set_playback_dma(chip, runtime->dma_addr, size);
	
	/* SPEAKER_ON not needed, since dma_on seems to also enable speaker */
	/* snd_sbdsp_command(chip, SB_DSP_SPEAKER_ON); */
	snd_sbdsp_command(chip, playback_cmd(chip).dsp_cmd);
	snd_sbdsp_command(chip, playback_cmd(chip).format);
	snd_sbdsp_command(chip, count & 0xff);
	snd_sbdsp_command(chip, count >> 8);
	snd_sbdsp_command(chip, playback_cmd(chip).dma_off);	
	spin_unlock_irq(&chip->reg_lock);
	
	return 0;
}