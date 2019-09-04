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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rtw_wfd_tdls_enable(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
#ifdef CONFIG_WFD

	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);

	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length -1  );

	if ( extra[ 0 ] == '0' )
	{
		padapter->wdinfo.wfd_tdls_enable = 0;
	}
	else
	{
		padapter->wdinfo.wfd_tdls_enable = 1;
	}

#endif //CONFIG_WFD
#endif //CONFIG_TDLS
	
	return ret;
}