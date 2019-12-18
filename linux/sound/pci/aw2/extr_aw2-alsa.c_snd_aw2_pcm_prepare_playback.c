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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; } ;
struct aw2_pcm_device {int /*<<< orphan*/  stream_number; struct aw2* chip; } ;
struct aw2 {int /*<<< orphan*/  mtx; int /*<<< orphan*/  saa7146; } ;
typedef  int /*<<< orphan*/  snd_aw2_saa7146_it_cb ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_aw2_saa7146_define_it_playback_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  snd_aw2_saa7146_pcm_init_playback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned long snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_period_elapsed ; 
 struct aw2_pcm_device* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_aw2_pcm_prepare_playback(struct snd_pcm_substream *substream)
{
	struct aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	struct aw2 *chip = pcm_device->chip;
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long period_size, buffer_size;

	mutex_lock(&chip->mtx);

	period_size = snd_pcm_lib_period_bytes(substream);
	buffer_size = snd_pcm_lib_buffer_bytes(substream);

	snd_aw2_saa7146_pcm_init_playback(&chip->saa7146,
					  pcm_device->stream_number,
					  runtime->dma_addr, period_size,
					  buffer_size);

	/* Define Interrupt callback */
	snd_aw2_saa7146_define_it_playback_callback(pcm_device->stream_number,
						    (snd_aw2_saa7146_it_cb)
						    snd_pcm_period_elapsed,
						    (void *)substream);

	mutex_unlock(&chip->mtx);

	return 0;
}