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
struct snd_pcm_runtime {struct nm256_stream* private_data; } ;
struct nm256_stream {scalar_t__ bufptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,unsigned long) ; 

__attribute__((used)) static int
snd_nm256_playback_copy_kernel(struct snd_pcm_substream *substream,
			       int channel, unsigned long pos,
			       void *src, unsigned long count)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nm256_stream *s = runtime->private_data;

	memcpy_toio(s->bufptr + pos, src, count);
	return 0;
}