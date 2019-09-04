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
struct frad_local {int (* deactivate ) (struct net_device*,struct net_device*) ;} ;
struct dlci_local {struct net_device* slave; } ;

/* Variables and functions */
 void* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int stub1 (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int dlci_close(struct net_device *dev)
{
	struct dlci_local	*dlp;
	struct frad_local	*flp;
	int			err;

	netif_stop_queue(dev);

	dlp = netdev_priv(dev);

	flp = netdev_priv(dlp->slave);
	err = (*flp->deactivate)(dlp->slave, dev);

	return 0;
}