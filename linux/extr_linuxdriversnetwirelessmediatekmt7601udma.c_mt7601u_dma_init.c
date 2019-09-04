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
struct mt7601u_dev {int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  tx_tasklet; } ;

/* Variables and functions */
 int ENOMEM ; 
 int mt7601u_alloc_rx (struct mt7601u_dev*) ; 
 int mt7601u_alloc_tx (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_dma_cleanup (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_rx_tasklet ; 
 int mt7601u_submit_rx (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_tx_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int mt7601u_dma_init(struct mt7601u_dev *dev)
{
	int ret = -ENOMEM;

	tasklet_init(&dev->tx_tasklet, mt7601u_tx_tasklet, (unsigned long) dev);
	tasklet_init(&dev->rx_tasklet, mt7601u_rx_tasklet, (unsigned long) dev);

	ret = mt7601u_alloc_tx(dev);
	if (ret)
		goto err;
	ret = mt7601u_alloc_rx(dev);
	if (ret)
		goto err;

	ret = mt7601u_submit_rx(dev);
	if (ret)
		goto err;

	return 0;
err:
	mt7601u_dma_cleanup(dev);
	return ret;
}