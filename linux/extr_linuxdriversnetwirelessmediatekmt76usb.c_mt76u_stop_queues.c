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
struct TYPE_2__ {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  rx_tasklet; } ;
struct mt76_dev {TYPE_1__ usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76u_stop_rx (struct mt76_dev*) ; 
 int /*<<< orphan*/  mt76u_stop_tx (struct mt76_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

void mt76u_stop_queues(struct mt76_dev *dev)
{
	tasklet_disable(&dev->usb.rx_tasklet);
	tasklet_disable(&dev->usb.tx_tasklet);

	mt76u_stop_rx(dev);
	mt76u_stop_tx(dev);
}