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
struct port {int /*<<< orphan*/  napi; TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qmgr_disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eth_rx_irq(void *pdev)
{
	struct net_device *dev = pdev;
	struct port *port = netdev_priv(dev);

#if DEBUG_RX
	printk(KERN_DEBUG "%s: eth_rx_irq\n", dev->name);
#endif
	qmgr_disable_irq(port->plat->rxq);
	napi_schedule(&port->napi);
}