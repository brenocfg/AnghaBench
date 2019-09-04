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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 size_t ANDROID_WIFI_CMD_SETBAND ; 
 int /*<<< orphan*/  GHZ_MAX ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/ * android_wifi_cmd_str ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int rtw_set_band (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int rtw_android_setband(struct net_device *net, char *command, int total_len)
{
	_adapter *adapter = (_adapter *)rtw_netdev_priv(net);
	char *arg = command + strlen(android_wifi_cmd_str[ANDROID_WIFI_CMD_SETBAND]) + 1;
	u32 band = GHZ_MAX;
	int ret = _FAIL;

	sscanf(arg, "%u", &band);
	ret = rtw_set_band(adapter, band);

	return (ret==_SUCCESS)?0:-1;
}