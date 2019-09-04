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
struct knav_dma_device {int max_tx_chan; TYPE_1__* reg_tx_chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ENABLE ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_hw_enable_all(struct knav_dma_device *dma)
{
	int i;

	for (i = 0; i < dma->max_tx_chan; i++) {
		writel_relaxed(0, &dma->reg_tx_chan[i].mode);
		writel_relaxed(DMA_ENABLE, &dma->reg_tx_chan[i].control);
	}
}