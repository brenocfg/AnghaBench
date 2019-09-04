#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct snd_dma_buffer {size_t bytes; int /*<<< orphan*/ * private_data; int /*<<< orphan*/  area; int /*<<< orphan*/  addr; TYPE_1__ dev; } ;
struct snd_pcm_substream {struct snd_dma_buffer dma_buffer; } ;
struct snd_pcm {TYPE_2__* card; TYPE_3__* streams; } ;
struct TYPE_8__ {size_t buffer_bytes_max; } ;
struct TYPE_7__ {struct snd_pcm_substream* substream; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ kirkwood_dma_snd_hw ; 

__attribute__((used)) static int kirkwood_dma_preallocate_dma_buffer(struct snd_pcm *pcm,
		int stream)
{
	struct snd_pcm_substream *substream = pcm->streams[stream].substream;
	struct snd_dma_buffer *buf = &substream->dma_buffer;
	size_t size = kirkwood_dma_snd_hw.buffer_bytes_max;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->area = dma_alloc_coherent(pcm->card->dev, size,
			&buf->addr, GFP_KERNEL);
	if (!buf->area)
		return -ENOMEM;
	buf->bytes = size;
	buf->private_data = NULL;

	return 0;
}