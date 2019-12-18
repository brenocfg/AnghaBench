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
struct TYPE_2__ {long buffer_bytes; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 long bytes_to_frames (struct snd_pcm_runtime*,long) ; 
 long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static long snd_pcm_alsa_frames(struct snd_pcm_substream *substream, long bytes)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	long buffer_size = snd_pcm_lib_buffer_bytes(substream);
	if (buffer_size == runtime->oss.buffer_bytes)
		return bytes_to_frames(runtime, bytes);
	return bytes_to_frames(runtime, (buffer_size * bytes) / runtime->oss.buffer_bytes);
}