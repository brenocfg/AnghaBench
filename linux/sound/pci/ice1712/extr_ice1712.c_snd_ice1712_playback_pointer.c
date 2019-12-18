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
struct snd_pcm_runtime {size_t buffer_size; } ;
struct snd_ice1712 {scalar_t__ ddma_port; } ;
typedef  size_t snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_IREG_PBK_CTRL ; 
 size_t bytes_to_frames (struct snd_pcm_runtime*,size_t) ; 
 size_t inw (scalar_t__) ; 
 int snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ice1712_playback_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	size_t ptr;

	if (!(snd_ice1712_read(ice, ICE1712_IREG_PBK_CTRL) & 1))
		return 0;
	ptr = runtime->buffer_size - inw(ice->ddma_port + 4);
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (ptr == runtime->buffer_size)
		ptr = 0;
	return ptr;
}