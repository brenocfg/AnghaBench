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
typedef  int u64 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {long buffer_bytes; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 long div_u64 (int,long) ; 
 long frames_to_bytes (struct snd_pcm_runtime*,long) ; 
 long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static long snd_pcm_oss_bytes(struct snd_pcm_substream *substream, long frames)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	long buffer_size = snd_pcm_lib_buffer_bytes(substream);
	long bytes = frames_to_bytes(runtime, frames);
	if (buffer_size == runtime->oss.buffer_bytes)
		return bytes;
#if BITS_PER_LONG >= 64
	return runtime->oss.buffer_bytes * bytes / buffer_size;
#else
	{
		u64 bsize = (u64)runtime->oss.buffer_bytes * (u64)bytes;
		return div_u64(bsize, buffer_size);
	}
#endif
}