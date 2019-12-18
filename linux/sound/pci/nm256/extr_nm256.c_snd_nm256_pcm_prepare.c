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
struct snd_pcm_runtime {int /*<<< orphan*/  periods; int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer_size; struct nm256_stream* private_data; } ;
struct nm256_stream {scalar_t__ running; scalar_t__ cur_period; int /*<<< orphan*/  periods; void* period_size; void* dma_size; } ;
struct nm256 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 void* frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_nm256_set_format (struct nm256*,struct nm256_stream*,struct snd_pcm_substream*) ; 
 struct nm256* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_nm256_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct nm256 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nm256_stream *s = runtime->private_data;

	if (snd_BUG_ON(!s))
		return -ENXIO;
	s->dma_size = frames_to_bytes(runtime, substream->runtime->buffer_size);
	s->period_size = frames_to_bytes(runtime, substream->runtime->period_size);
	s->periods = substream->runtime->periods;
	s->cur_period = 0;

	spin_lock_irq(&chip->reg_lock);
	s->running = 0;
	snd_nm256_set_format(chip, s, substream);
	spin_unlock_irq(&chip->reg_lock);

	return 0;
}