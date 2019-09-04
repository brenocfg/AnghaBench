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
struct snd_pcm_runtime {void* dma_area; int dma_bytes; int channels; } ;

/* Variables and functions */

__attribute__((used)) static void *get_dma_ptr(struct snd_pcm_runtime *runtime,
			   int channel, unsigned long hwoff)
{
	return runtime->dma_area + hwoff +
		channel * (runtime->dma_bytes / runtime->channels);
}