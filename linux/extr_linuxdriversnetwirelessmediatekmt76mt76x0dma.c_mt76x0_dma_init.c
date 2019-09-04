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
struct mt76x0_dev {int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  tx_tasklet; } ;

/* Variables and functions */
 int ENOMEM ; 
 int mt76x0_alloc_rx (struct mt76x0_dev*) ; 
 int mt76x0_alloc_tx (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_dma_cleanup (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_rx_tasklet ; 
 int mt76x0_submit_rx (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_tx_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int mt76x0_dma_init(struct mt76x0_dev *dev)
{
	int ret = -ENOMEM;

	tasklet_init(&dev->tx_tasklet, mt76x0_tx_tasklet, (unsigned long) dev);
	tasklet_init(&dev->rx_tasklet, mt76x0_rx_tasklet, (unsigned long) dev);

	ret = mt76x0_alloc_tx(dev);
	if (ret)
		goto err;
	ret = mt76x0_alloc_rx(dev);
	if (ret)
		goto err;

	ret = mt76x0_submit_rx(dev);
	if (ret)
		goto err;

	return 0;
err:
	mt76x0_dma_cleanup(dev);
	return ret;
}