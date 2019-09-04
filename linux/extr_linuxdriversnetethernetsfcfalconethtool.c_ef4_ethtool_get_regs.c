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
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct ef4_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_nic_get_regs (struct ef4_nic*,void*) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ef4_ethtool_get_regs(struct net_device *net_dev,
				 struct ethtool_regs *regs, void *buf)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	regs->version = efx->type->revision;
	ef4_nic_get_regs(efx, buf);
}