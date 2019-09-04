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
typedef  int u32 ;
struct rhine_private {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int IntrLinkChange ; 
 int IntrStatsMax ; 
 int RHINE_EVENT ; 
 int RHINE_EVENT_NAPI ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct rhine_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct rhine_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int rhine_get_events (struct rhine_private*) ; 
 int /*<<< orphan*/  rhine_irq_disable (struct rhine_private*) ; 

__attribute__((used)) static irqreturn_t rhine_interrupt(int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct rhine_private *rp = netdev_priv(dev);
	u32 status;
	int handled = 0;

	status = rhine_get_events(rp);

	netif_dbg(rp, intr, dev, "Interrupt, status %08x\n", status);

	if (status & RHINE_EVENT) {
		handled = 1;

		rhine_irq_disable(rp);
		napi_schedule(&rp->napi);
	}

	if (status & ~(IntrLinkChange | IntrStatsMax | RHINE_EVENT_NAPI)) {
		netif_err(rp, intr, dev, "Something Wicked happened! %08x\n",
			  status);
	}

	return IRQ_RETVAL(handled);
}