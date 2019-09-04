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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _nic_hdl ;

/* Variables and functions */

inline int _rtw_netif_rx(_nic_hdl ndev, struct sk_buff *skb)
{
#ifdef PLATFORM_LINUX
	skb->dev = ndev;
	return netif_rx(skb);
#endif /* PLATFORM_LINUX */

#ifdef PLATFORM_FREEBSD
	return (*ndev->if_input)(ndev, skb);
#endif /* PLATFORM_FREEBSD */
}