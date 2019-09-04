#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct port {size_t id; TYPE_1__* plat; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  txdone; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  rxfree; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (size_t,struct net_device*) ;int /*<<< orphan*/  txreadyq; } ;

/* Variables and functions */
 int MAX_CLOSE_WAIT ; 
 int RX_DESCS ; 
 int TX_DESCS ; 
 int /*<<< orphan*/  destroy_hdlc_queues (struct port*) ; 
 struct port* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 int /*<<< orphan*/  hss_stop_hdlc (struct port*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_crit (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  npe_lock ; 
 int /*<<< orphan*/  ports_open ; 
 int /*<<< orphan*/  qmgr_disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ queue_get_desc (int /*<<< orphan*/ ,struct port*,int) ; 
 TYPE_2__* queue_ids ; 
 int /*<<< orphan*/  release_hdlc_queues (struct port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (size_t,struct net_device*) ; 

__attribute__((used)) static int hss_hdlc_close(struct net_device *dev)
{
	struct port *port = dev_to_port(dev);
	unsigned long flags;
	int i, buffs = RX_DESCS; /* allocated RX buffers */

	spin_lock_irqsave(&npe_lock, flags);
	ports_open--;
	qmgr_disable_irq(queue_ids[port->id].rx);
	netif_stop_queue(dev);
	napi_disable(&port->napi);

	hss_stop_hdlc(port);

	while (queue_get_desc(queue_ids[port->id].rxfree, port, 0) >= 0)
		buffs--;
	while (queue_get_desc(queue_ids[port->id].rx, port, 0) >= 0)
		buffs--;

	if (buffs)
		netdev_crit(dev, "unable to drain RX queue, %i buffer(s) left in NPE\n",
			    buffs);

	buffs = TX_DESCS;
	while (queue_get_desc(queue_ids[port->id].tx, port, 1) >= 0)
		buffs--; /* cancel TX */

	i = 0;
	do {
		while (queue_get_desc(port->plat->txreadyq, port, 1) >= 0)
			buffs--;
		if (!buffs)
			break;
	} while (++i < MAX_CLOSE_WAIT);

	if (buffs)
		netdev_crit(dev, "unable to drain TX queue, %i buffer(s) left in NPE\n",
			    buffs);
#if DEBUG_CLOSE
	if (!buffs)
		printk(KERN_DEBUG "Draining TX queues took %i cycles\n", i);
#endif
	qmgr_disable_irq(queue_ids[port->id].txdone);

	if (port->plat->close)
		port->plat->close(port->id, dev);
	spin_unlock_irqrestore(&npe_lock, flags);

	destroy_hdlc_queues(port);
	release_hdlc_queues(port);
	hdlc_close(dev);
	return 0;
}