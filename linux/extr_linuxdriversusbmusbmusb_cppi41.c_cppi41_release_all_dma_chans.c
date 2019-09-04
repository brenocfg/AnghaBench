#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dma_chan {int dummy; } ;
struct cppi41_dma_controller {int num_channels; TYPE_2__* rx_channel; TYPE_1__* tx_channel; } ;
struct TYPE_4__ {struct dma_chan* dc; } ;
struct TYPE_3__ {struct dma_chan* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 

__attribute__((used)) static void cppi41_release_all_dma_chans(struct cppi41_dma_controller *ctrl)
{
	struct dma_chan *dc;
	int i;

	for (i = 0; i < ctrl->num_channels; i++) {
		dc = ctrl->tx_channel[i].dc;
		if (dc)
			dma_release_channel(dc);
		dc = ctrl->rx_channel[i].dc;
		if (dc)
			dma_release_channel(dc);
	}
}