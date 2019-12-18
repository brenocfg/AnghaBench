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
struct snd_pcm_runtime {unsigned char* dma_area; } ;
struct es1938 {unsigned long dma1_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,unsigned long) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_capture_copy_kernel(struct snd_pcm_substream *substream,
					  int channel, unsigned long pos,
					  void *dst, unsigned long count)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct es1938 *chip = snd_pcm_substream_chip(substream);

	if (snd_BUG_ON(pos + count > chip->dma1_size))
		return -EINVAL;
	if (pos + count < chip->dma1_size) {
		memcpy(dst, runtime->dma_area + pos + 1, count);
	} else {
		memcpy(dst, runtime->dma_area + pos + 1, count - 1);
		runtime->dma_area[0] = *((unsigned char *)dst + count - 1);
	}
	return 0;
}