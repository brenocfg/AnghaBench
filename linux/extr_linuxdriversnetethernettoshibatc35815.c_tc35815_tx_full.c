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
struct tc35815_local {int tfd_start; int tfd_end; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int TX_FD_NUM ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int tc35815_tx_full(struct net_device *dev)
{
	struct tc35815_local *lp = netdev_priv(dev);
	return (lp->tfd_start + 1) % TX_FD_NUM == lp->tfd_end;
}