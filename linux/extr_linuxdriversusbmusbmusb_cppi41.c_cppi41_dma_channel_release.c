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
struct dma_channel {scalar_t__ actual_len; int /*<<< orphan*/  status; struct cppi41_dma_channel* private_data; } ;
struct cppi41_dma_channel {scalar_t__ is_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DMA_STATUS_FREE ; 
 int /*<<< orphan*/  trace_musb_cppi41_free (struct cppi41_dma_channel*) ; 

__attribute__((used)) static void cppi41_dma_channel_release(struct dma_channel *channel)
{
	struct cppi41_dma_channel *cppi41_channel = channel->private_data;

	trace_musb_cppi41_free(cppi41_channel);
	if (cppi41_channel->is_allocated) {
		cppi41_channel->is_allocated = 0;
		channel->status = MUSB_DMA_STATUS_FREE;
		channel->actual_len = 0;
	}
}