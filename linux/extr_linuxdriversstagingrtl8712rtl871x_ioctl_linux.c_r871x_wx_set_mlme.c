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
struct iw_mlme {int cmd; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r8712_set_802_11_disassociate (struct _adapter*) ; 

__attribute__((used)) static int r871x_wx_set_mlme(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	int ret = 0;
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_mlme *mlme = (struct iw_mlme *) extra;

	if (mlme == NULL)
		return -1;
	switch (mlme->cmd) {
	case IW_MLME_DEAUTH:
		if (!r8712_set_802_11_disassociate(padapter))
			ret = -1;
		break;
	case IW_MLME_DISASSOC:
		if (!r8712_set_802_11_disassociate(padapter))
			ret = -1;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return ret;
}