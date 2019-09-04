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
struct txx9aclc_dmadata {int buffer_bytes; int period_bytes; int frag_bytes; int frags; scalar_t__ pos; scalar_t__ frag_count; int /*<<< orphan*/  dma_addr; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; struct txx9aclc_dmadata* private_data; } ;

/* Variables and functions */
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static int txx9aclc_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct txx9aclc_dmadata *dmadata = runtime->private_data;

	dmadata->dma_addr = runtime->dma_addr;
	dmadata->buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
	dmadata->period_bytes = snd_pcm_lib_period_bytes(substream);

	if (dmadata->buffer_bytes == dmadata->period_bytes) {
		dmadata->frag_bytes = dmadata->period_bytes >> 1;
		dmadata->frags = 2;
	} else {
		dmadata->frag_bytes = dmadata->period_bytes;
		dmadata->frags = dmadata->buffer_bytes / dmadata->period_bytes;
	}
	dmadata->frag_count = 0;
	dmadata->pos = 0;
	return 0;
}