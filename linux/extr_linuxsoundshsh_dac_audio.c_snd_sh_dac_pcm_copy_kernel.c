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
struct snd_sh_dac {scalar_t__ empty; scalar_t__ data_buffer; scalar_t__ buffer_end; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dac_audio_start_timer (struct snd_sh_dac*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,unsigned long) ; 
 struct snd_sh_dac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_sh_dac_pcm_copy_kernel(struct snd_pcm_substream *substream,
				      int channel, unsigned long pos,
				      void *src, unsigned long count)
{
	/* channel is not used (interleaved data) */
	struct snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	memcpy_toio(chip->data_buffer + pos, src, count);
	chip->buffer_end = chip->data_buffer + pos + count;

	if (chip->empty) {
		chip->empty = 0;
		dac_audio_start_timer(chip);
	}

	return 0;
}