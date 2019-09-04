#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_4__ {scalar_t__ bup; TYPE_1__ eeprompriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_net_set_mac_address(struct net_device *pnetdev, void *p)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(pnetdev);
	struct sockaddr *addr = p;

	if(padapter->bup == _FALSE)
	{
		//DBG_871X("r8711_net_set_mac_address(), MAC=%x:%x:%x:%x:%x:%x\n", addr->sa_data[0], addr->sa_data[1], addr->sa_data[2], addr->sa_data[3],
		//addr->sa_data[4], addr->sa_data[5]);
		_rtw_memcpy(padapter->eeprompriv.mac_addr, addr->sa_data, ETH_ALEN);
		//_rtw_memcpy(pnetdev->dev_addr, addr->sa_data, ETH_ALEN);
		//padapter->bset_hwaddr = _TRUE;
	}

	return 0;
}