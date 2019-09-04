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
struct TYPE_2__ {int /*<<< orphan*/  DriverLock; } ;
struct s_smc {TYPE_1__ os; } ;
struct net_device {int dummy; } ;
typedef  TYPE_1__ skfddi_priv ;

/* Variables and functions */
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skfp_ctl_set_multicast_list_wo_lock (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void skfp_ctl_set_multicast_list(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;
	unsigned long Flags;

	spin_lock_irqsave(&bp->DriverLock, Flags);
	skfp_ctl_set_multicast_list_wo_lock(dev);
	spin_unlock_irqrestore(&bp->DriverLock, Flags);
}