#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_10__ {TYPE_4__ dev; } ;
struct snd_pcm_substream {TYPE_5__ dma_buffer; TYPE_3__* ops; TYPE_2__* runtime; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmap; } ;
struct TYPE_6__ {int info; } ;
struct TYPE_7__ {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ SNDRV_DMA_TYPE_DEV ; 
 int SNDRV_PCM_INFO_MMAP ; 

__attribute__((used)) static bool hw_support_mmap(struct snd_pcm_substream *substream)
{
	if (!(substream->runtime->hw.info & SNDRV_PCM_INFO_MMAP))
		return false;
	/* architecture supports dma_mmap_coherent()? */
#if defined(CONFIG_ARCH_NO_COHERENT_DMA_MMAP) || !defined(CONFIG_HAS_DMA)
	if (!substream->ops->mmap &&
	    substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV)
		return false;
#endif
	return true;
}