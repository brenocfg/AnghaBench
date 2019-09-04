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
 size_t ANDROID_WIFI_CMD_BLOCK ; 
 int /*<<< orphan*/ * android_wifi_cmd_str ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int rtw_android_set_block(struct net_device *net, char *command, int total_len)
{
	_adapter *adapter = (_adapter *)rtw_netdev_priv(net);
	char *block_value = command + strlen(android_wifi_cmd_str[ANDROID_WIFI_CMD_BLOCK]) + 1;

	#ifdef CONFIG_IOCTL_CFG80211
	wdev_to_priv(adapter->rtw_wdev)->block = (*block_value=='0')?_FALSE:_TRUE;
	#endif
	
	return 0;
}