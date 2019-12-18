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
struct sw {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  eth_schedule_poll (struct sw*) ; 
 struct sw* netdev_priv (struct net_device*) ; 

irqreturn_t eth_rx_irq(int irq, void *pdev)
{
	struct net_device *dev = pdev;
	struct sw *sw = netdev_priv(dev);
	eth_schedule_poll(sw);
	return (IRQ_HANDLED);
}