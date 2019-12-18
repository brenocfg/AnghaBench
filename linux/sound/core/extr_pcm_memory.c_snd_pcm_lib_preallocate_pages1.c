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
struct TYPE_2__ {scalar_t__ bytes; } ;
struct snd_pcm_substream {scalar_t__ number; scalar_t__ buffer_bytes_max; size_t dma_max; TYPE_1__ dma_buffer; } ;

/* Variables and functions */
 scalar_t__ maximum_substreams ; 
 scalar_t__ preallocate_dma ; 
 int /*<<< orphan*/  preallocate_info_init (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  preallocate_pcm_pages (struct snd_pcm_substream*,size_t) ; 

__attribute__((used)) static void snd_pcm_lib_preallocate_pages1(struct snd_pcm_substream *substream,
					  size_t size, size_t max)
{

	if (size > 0 && preallocate_dma && substream->number < maximum_substreams)
		preallocate_pcm_pages(substream, size);

	if (substream->dma_buffer.bytes > 0)
		substream->buffer_bytes_max = substream->dma_buffer.bytes;
	substream->dma_max = max;
	preallocate_info_init(substream);
}