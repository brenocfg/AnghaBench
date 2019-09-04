#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wlan_network {int dummy; } ;
struct net_device {int dummy; } ;
struct mlme_priv {struct wlan_network cur_network; } ;
struct TYPE_3__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int rtw_get_cur_max_rate (TYPE_1__*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int snprintf (char*,int,char*,int) ; 

int rtw_android_get_link_speed(struct net_device *net, char *command, int total_len)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(net);
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);	
	struct	wlan_network	*pcur_network = &pmlmepriv->cur_network;
	int bytes_written = 0;
	u16 link_speed = 0;

	link_speed = rtw_get_cur_max_rate(padapter)/10;
	bytes_written = snprintf(command, total_len, "LinkSpeed %d", link_speed);

	return bytes_written;
}