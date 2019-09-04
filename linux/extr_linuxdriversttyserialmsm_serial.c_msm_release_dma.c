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
struct msm_dma {int /*<<< orphan*/  virt; scalar_t__ chan; } ;
struct msm_port {int /*<<< orphan*/  uart; struct msm_dma rx_dma; struct msm_dma tx_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct msm_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_stop_dma (int /*<<< orphan*/ *,struct msm_dma*) ; 

__attribute__((used)) static void msm_release_dma(struct msm_port *msm_port)
{
	struct msm_dma *dma;

	dma = &msm_port->tx_dma;
	if (dma->chan) {
		msm_stop_dma(&msm_port->uart, dma);
		dma_release_channel(dma->chan);
	}

	memset(dma, 0, sizeof(*dma));

	dma = &msm_port->rx_dma;
	if (dma->chan) {
		msm_stop_dma(&msm_port->uart, dma);
		dma_release_channel(dma->chan);
		kfree(dma->virt);
	}

	memset(dma, 0, sizeof(*dma));
}