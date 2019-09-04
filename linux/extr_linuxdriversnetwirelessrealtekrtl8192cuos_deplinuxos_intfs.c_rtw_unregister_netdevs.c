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
struct dvobj_priv {int iface_nums; TYPE_1__** padapters; } ;
struct TYPE_2__ {scalar_t__ DriverState; struct net_device* pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ DRIVER_DISAPPEAR ; 
 int /*<<< orphan*/  rtw_proc_remove_one (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void rtw_unregister_netdevs(struct dvobj_priv *dvobj)
{
	int i;
	_adapter *padapter = NULL;

	for (i=0;i<dvobj->iface_nums;i++) {
		struct net_device *pnetdev = NULL;

		padapter = dvobj->padapters[i];

		if (padapter == NULL)
			continue;

		pnetdev = padapter->pnetdev;

		if((padapter->DriverState != DRIVER_DISAPPEAR) && pnetdev) {
			unregister_netdev(pnetdev); //will call netdev_close()
			rtw_proc_remove_one(pnetdev);
		}

		#ifdef CONFIG_IOCTL_CFG80211
		rtw_wdev_unregister(padapter->rtw_wdev);
		#endif
	}

}