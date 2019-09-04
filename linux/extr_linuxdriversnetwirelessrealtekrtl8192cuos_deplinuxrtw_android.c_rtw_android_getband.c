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
struct net_device {int dummy; } ;
struct TYPE_2__ {int setband; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int snprintf (char*,int,char*,int) ; 

int rtw_android_getband(struct net_device *net, char *command, int total_len)
{
	_adapter *adapter = (_adapter *)rtw_netdev_priv(net);
	int bytes_written = 0;

	bytes_written = snprintf(command, total_len, "%u", adapter->setband);

	return bytes_written;
}