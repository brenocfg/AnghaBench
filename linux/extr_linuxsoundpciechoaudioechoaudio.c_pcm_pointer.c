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
struct snd_pcm_runtime {size_t buffer_size; struct audiopipe* private_data; } ;
struct audiopipe {size_t last_counter; int /*<<< orphan*/  position; int /*<<< orphan*/ * dma_counter; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 size_t bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct audiopipe *pipe = runtime->private_data;
	size_t cnt, bufsize, pos;

	cnt = le32_to_cpu(*pipe->dma_counter);
	pipe->position += cnt - pipe->last_counter;
	pipe->last_counter = cnt;
	bufsize = substream->runtime->buffer_size;
	pos = bytes_to_frames(substream->runtime, pipe->position);

	while (pos >= bufsize) {
		pipe->position -= frames_to_bytes(substream->runtime, bufsize);
		pos -= bufsize;
	}
	return pos;
}