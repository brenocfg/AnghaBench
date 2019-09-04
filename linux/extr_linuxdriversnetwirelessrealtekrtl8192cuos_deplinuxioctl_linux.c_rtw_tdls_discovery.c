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

__attribute__((used)) static int rtw_tdls_discovery(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;

#ifdef CONFIG_TDLS
	
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	printk( "[%s] %s %d\n", __FUNCTION__, extra, wrqu->data.length -1  );

	issue_tdls_dis_req(padapter, NULL);

#endif //CONFIG_TDLS

	return ret;
}