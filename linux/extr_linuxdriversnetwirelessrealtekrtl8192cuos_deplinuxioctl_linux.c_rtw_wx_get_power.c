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
struct TYPE_2__ {int disabled; scalar_t__ fixed; scalar_t__ value; } ;
union iwreq_data {TYPE_1__ power; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rtw_wx_get_power(struct net_device *dev, 
			     struct iw_request_info *info, 
			     union iwreq_data *wrqu, char *extra)
{
	//_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	
	wrqu->power.value = 0;
	wrqu->power.fixed = 0;	/* no auto select */
	wrqu->power.disabled = 1;
	
	return 0;

}