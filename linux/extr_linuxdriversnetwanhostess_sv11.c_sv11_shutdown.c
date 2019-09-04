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
struct TYPE_2__ {int /*<<< orphan*/  netdevice; scalar_t__ ctrlio; int /*<<< orphan*/  txdma; int /*<<< orphan*/  rxdma; } ;
struct z8530_dev {TYPE_1__ chanA; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int dma ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct z8530_dev*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct z8530_dev*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  unregister_hdlc_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8530_shutdown (struct z8530_dev*) ; 

__attribute__((used)) static void sv11_shutdown(struct z8530_dev *dev)
{
	unregister_hdlc_device(dev->chanA.netdevice);
	z8530_shutdown(dev);
	free_irq(dev->irq, dev);
	if (dma) {
		if (dma == 1)
			free_dma(dev->chanA.rxdma);
		free_dma(dev->chanA.txdma);
	}
	release_region(dev->chanA.ctrlio - 1, 8);
	free_netdev(dev->chanA.netdevice);
	kfree(dev);
}