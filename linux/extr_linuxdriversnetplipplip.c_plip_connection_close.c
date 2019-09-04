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
struct plip_local {int dummy; } ;
struct net_local {scalar_t__ connection; int /*<<< orphan*/  pardev; scalar_t__ port_owner; scalar_t__ should_relinquish; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int OK ; 
 scalar_t__ PLIP_CN_CLOSING ; 
 scalar_t__ PLIP_CN_NONE ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
plip_connection_close(struct net_device *dev, struct net_local *nl,
		      struct plip_local *snd, struct plip_local *rcv)
{
	spin_lock_irq(&nl->lock);
	if (nl->connection == PLIP_CN_CLOSING) {
		nl->connection = PLIP_CN_NONE;
		netif_wake_queue (dev);
	}
	spin_unlock_irq(&nl->lock);
	if (nl->should_relinquish) {
		nl->should_relinquish = nl->port_owner = 0;
		parport_release(nl->pardev);
	}
	return OK;
}