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

__attribute__((used)) static int rtw_tdls_getip(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
#ifdef CONFIG_WFD
	
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct tdls_info *ptdlsinfo = &padapter->tdlsinfo;
	struct wifi_display_info *pwfd_info = ptdlsinfo->wfd_info;
	
	printk( "[%s]\n", __FUNCTION__);

	sprintf( extra, "\n\n%u.%u.%u.%u\n", 
		pwfd_info->peer_ip_address[0], pwfd_info->peer_ip_address[1], 
		pwfd_info->peer_ip_address[2], pwfd_info->peer_ip_address[3]
		);

	printk( "[%s] IP=%u.%u.%u.%u\n", __FUNCTION__,
		pwfd_info->peer_ip_address[0], pwfd_info->peer_ip_address[1], 
		pwfd_info->peer_ip_address[2], pwfd_info->peer_ip_address[3]
		);
	
	wrqu->data.length = strlen( extra );

#endif //CONFIG_WFD	
#endif //CONFIG_TDLS

	return ret;
}