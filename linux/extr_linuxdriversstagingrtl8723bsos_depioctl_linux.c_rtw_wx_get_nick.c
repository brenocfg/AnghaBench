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
struct TYPE_2__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int rtw_wx_get_nick(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	/* struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev); */
	 /* struct mlme_priv *pmlmepriv = &(padapter->mlmepriv); */
	 /* struct security_priv *psecuritypriv = &padapter->securitypriv; */

	if (extra) {
		wrqu->data.length = 14;
		wrqu->data.flags = 1;
		memcpy(extra, "<WIFI@REALTEK>", 14);
	}
	return 0;
}