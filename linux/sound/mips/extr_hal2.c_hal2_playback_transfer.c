#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct snd_pcm_indirect {int hw_data; scalar_t__ sw_data; } ;
struct TYPE_4__ {unsigned char* buffer; } ;
struct snd_hal2 {TYPE_3__* card; TYPE_1__ dac; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,size_t) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void hal2_playback_transfer(struct snd_pcm_substream *substream,
				   struct snd_pcm_indirect *rec, size_t bytes)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	unsigned char *buf = hal2->dac.buffer + rec->hw_data;

	memcpy(buf, substream->runtime->dma_area + rec->sw_data, bytes);
	dma_cache_sync(hal2->card->dev, buf, bytes, DMA_TO_DEVICE);

}