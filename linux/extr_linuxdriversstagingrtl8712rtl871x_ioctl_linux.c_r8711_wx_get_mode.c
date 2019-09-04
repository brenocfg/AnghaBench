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
union iwreq_data {int /*<<< orphan*/  mode; } ;
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_AUTO ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  IW_MODE_MASTER ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int r8711_wx_get_mode(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		wrqu->mode = IW_MODE_INFRA;
	else if (check_fwstate(pmlmepriv,
		 WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE))
		wrqu->mode = IW_MODE_ADHOC;
	else if (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		wrqu->mode = IW_MODE_MASTER;
	else
		wrqu->mode = IW_MODE_AUTO;
	return 0;
}