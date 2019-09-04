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
struct net_device {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  low_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int STATUS_ASSOCIATED ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ipw2100_open(struct net_device *dev)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	unsigned long flags;
	IPW_DEBUG_INFO("dev->open\n");

	spin_lock_irqsave(&priv->low_lock, flags);
	if (priv->status & STATUS_ASSOCIATED) {
		netif_carrier_on(dev);
		netif_start_queue(dev);
	}
	spin_unlock_irqrestore(&priv->low_lock, flags);

	return 0;
}