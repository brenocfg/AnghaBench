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
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/ * dma_rx_channel; int /*<<< orphan*/ * dma_tx_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_ngd_exit_dma(struct qcom_slim_ngd_ctrl *ctrl)
{
	if (ctrl->dma_rx_channel) {
		dmaengine_terminate_sync(ctrl->dma_rx_channel);
		dma_release_channel(ctrl->dma_rx_channel);
	}

	if (ctrl->dma_tx_channel) {
		dmaengine_terminate_sync(ctrl->dma_tx_channel);
		dma_release_channel(ctrl->dma_tx_channel);
	}

	ctrl->dma_tx_channel = ctrl->dma_rx_channel = NULL;

	return 0;
}