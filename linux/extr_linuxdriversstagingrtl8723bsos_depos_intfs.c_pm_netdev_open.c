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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 scalar_t__ _SUCCESS ; 
 int _netdev_open (struct net_device*) ; 
 TYPE_1__* adapter_to_dvobj (struct adapter*) ; 
 scalar_t__ ips_netdrv_open (struct adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int pm_netdev_open(struct net_device *pnetdev, u8 bnormal)
{
	int status = -1;

	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);

	if (true == bnormal) {
		if (mutex_lock_interruptible(&(adapter_to_dvobj(padapter)->hw_init_mutex)) == 0) {
			status = _netdev_open(pnetdev);
			mutex_unlock(&(adapter_to_dvobj(padapter)->hw_init_mutex));
		}
	}
	else
		status =  (_SUCCESS == ips_netdrv_open(padapter)) ? (0) : (-1);

	return status;
}