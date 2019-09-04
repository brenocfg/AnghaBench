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
struct mt76x0_dev {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  rx_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x0_free_rx (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_free_tx (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_kill_rx (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void mt76x0_dma_cleanup(struct mt76x0_dev *dev)
{
	mt76x0_kill_rx(dev);

	tasklet_kill(&dev->rx_tasklet);

	mt76x0_free_rx(dev);
	mt76x0_free_tx(dev);

	tasklet_kill(&dev->tx_tasklet);
}