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
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_2__ {int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _netdev_open (struct net_device*) ; 
 TYPE_1__* adapter_to_dvobj (int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

int netdev_open(struct net_device *pnetdev)
{
	int ret;
	_adapter *padapter = (_adapter *)rtw_netdev_priv(pnetdev);

	_enter_critical_mutex(&(adapter_to_dvobj(padapter)->hw_init_mutex), NULL);
	ret = _netdev_open(pnetdev);
	_exit_critical_mutex(&(adapter_to_dvobj(padapter)->hw_init_mutex), NULL);

	return ret;
}