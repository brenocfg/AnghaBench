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
struct port {size_t id; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 struct port* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmgr_disable_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__* queue_ids ; 

__attribute__((used)) static void hss_hdlc_rx_irq(void *pdev)
{
	struct net_device *dev = pdev;
	struct port *port = dev_to_port(dev);

#if DEBUG_RX
	printk(KERN_DEBUG "%s: hss_hdlc_rx_irq\n", dev->name);
#endif
	qmgr_disable_irq(queue_ids[port->id].rx);
	napi_schedule(&port->napi);
}