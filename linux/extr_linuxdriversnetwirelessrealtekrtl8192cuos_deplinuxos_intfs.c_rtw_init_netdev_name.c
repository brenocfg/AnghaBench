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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 scalar_t__ dev_alloc_name (struct net_device*,char const*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/ * rtw_netdev_priv (struct net_device*) ; 

int rtw_init_netdev_name(struct net_device *pnetdev, const char *ifname)
{
	_adapter *padapter = rtw_netdev_priv(pnetdev);

#ifdef CONFIG_EASY_REPLACEMENT
	struct net_device	*TargetNetdev = NULL;
	_adapter			*TargetAdapter = NULL;
	struct net 		*devnet = NULL;

	if(padapter->bDongle == 1)
	{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
		TargetNetdev = dev_get_by_name("wlan0");
#else
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))
		devnet = pnetdev->nd_net;
	#else
		devnet = dev_net(pnetdev);
	#endif
		TargetNetdev = dev_get_by_name(devnet, "wlan0");
#endif
		if(TargetNetdev) {
			DBG_871X("Force onboard module driver disappear !!!\n");
			TargetAdapter = rtw_netdev_priv(TargetNetdev);
			TargetAdapter->DriverState = DRIVER_DISAPPEAR;

			padapter->pid[0] = TargetAdapter->pid[0];
			padapter->pid[1] = TargetAdapter->pid[1];
			padapter->pid[2] = TargetAdapter->pid[2];

			dev_put(TargetNetdev);
			unregister_netdev(TargetNetdev);

			if(TargetAdapter->chip_type == padapter->chip_type)
				rtw_proc_remove_one(TargetNetdev);

			padapter->DriverState = DRIVER_REPLACE_DONGLE;
		}
	}
#endif //CONFIG_EASY_REPLACEMENT

	if(dev_alloc_name(pnetdev, ifname) < 0)
	{
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("dev_alloc_name, fail! \n"));
	}

	netif_carrier_off(pnetdev);
	//rtw_netif_stop_queue(pnetdev);

	return 0;
}