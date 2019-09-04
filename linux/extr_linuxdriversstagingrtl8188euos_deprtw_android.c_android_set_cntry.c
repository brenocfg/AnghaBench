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
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t ANDROID_WIFI_CMD_COUNTRY ; 
 int _SUCCESS ; 
 int /*<<< orphan*/ * android_wifi_cmd_str ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int rtw_set_country (struct adapter*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int android_set_cntry(struct net_device *net, char *command,
			     int total_len)
{
	struct adapter *adapter = (struct adapter *)rtw_netdev_priv(net);
	char *country_code = command + strlen(android_wifi_cmd_str[ANDROID_WIFI_CMD_COUNTRY]) + 1;
	int ret;

	ret = rtw_set_country(adapter, country_code);
	return (ret == _SUCCESS) ? 0 : -1;
}