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
struct sgiseeq_regs {int dummy; } ;
struct sgiseeq_private {int /*<<< orphan*/  hregs; struct sgiseeq_regs* sregs; } ;
struct net_device {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (unsigned int,struct net_device*) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  reset_hpc3_and_seeq (int /*<<< orphan*/ ,struct sgiseeq_regs*) ; 
 int /*<<< orphan*/  seeq_purge_ring (struct net_device*) ; 

__attribute__((used)) static int sgiseeq_close(struct net_device *dev)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct sgiseeq_regs *sregs = sp->sregs;
	unsigned int irq = dev->irq;

	netif_stop_queue(dev);

	/* Shutdown the Seeq. */
	reset_hpc3_and_seeq(sp->hregs, sregs);
	free_irq(irq, dev);
	seeq_purge_ring(dev);

	return 0;
}