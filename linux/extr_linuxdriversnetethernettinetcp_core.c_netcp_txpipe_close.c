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
struct netcp_tx_pipe {int /*<<< orphan*/ * dma_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  knav_dma_close_channel (int /*<<< orphan*/ *) ; 

int netcp_txpipe_close(struct netcp_tx_pipe *tx_pipe)
{
	if (tx_pipe->dma_channel) {
		knav_dma_close_channel(tx_pipe->dma_channel);
		tx_pipe->dma_channel = NULL;
	}
	return 0;
}