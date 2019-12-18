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
struct fsl_dma_private {size_t current_link; int dma_buf_next; int dma_buf_end; int dma_buf_phys; scalar_t__ period_size; TYPE_1__* substream; struct fsl_dma_link_descriptor* link; } ;
struct fsl_dma_link_descriptor {void* dest_attr; void* dest_addr; void* source_attr; void* source_addr; } ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 int CCSR_DMA_ATR_SNOOP ; 
 size_t NUM_DMA_LINKS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 void* cpu_to_be32 (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void fsl_dma_update_pointers(struct fsl_dma_private *dma_private)
{
	struct fsl_dma_link_descriptor *link =
		&dma_private->link[dma_private->current_link];

	/* Update our link descriptors to point to the next period. On a 36-bit
	 * system, we also need to update the ESAD bits.  We also set (keep) the
	 * snoop bits.  See the comments in fsl_dma_hw_params() about snooping.
	 */
	if (dma_private->substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		link->source_addr = cpu_to_be32(dma_private->dma_buf_next);
#ifdef CONFIG_PHYS_64BIT
		link->source_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
			upper_32_bits(dma_private->dma_buf_next));
#endif
	} else {
		link->dest_addr = cpu_to_be32(dma_private->dma_buf_next);
#ifdef CONFIG_PHYS_64BIT
		link->dest_attr = cpu_to_be32(CCSR_DMA_ATR_SNOOP |
			upper_32_bits(dma_private->dma_buf_next));
#endif
	}

	/* Update our variables for next time */
	dma_private->dma_buf_next += dma_private->period_size;

	if (dma_private->dma_buf_next >= dma_private->dma_buf_end)
		dma_private->dma_buf_next = dma_private->dma_buf_phys;

	if (++dma_private->current_link >= NUM_DMA_LINKS)
		dma_private->current_link = 0;
}