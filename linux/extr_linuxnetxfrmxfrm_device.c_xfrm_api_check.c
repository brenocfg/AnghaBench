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
struct net_device {int features; } ;

/* Variables and functions */
 int NETIF_F_HW_ESP ; 
 int NETIF_F_HW_ESP_TX_CSUM ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 

__attribute__((used)) static int xfrm_api_check(struct net_device *dev)
{
#ifdef CONFIG_XFRM_OFFLOAD
	if ((dev->features & NETIF_F_HW_ESP_TX_CSUM) &&
	    !(dev->features & NETIF_F_HW_ESP))
		return NOTIFY_BAD;

	if ((dev->features & NETIF_F_HW_ESP) &&
	    (!(dev->xfrmdev_ops &&
	       dev->xfrmdev_ops->xdo_dev_state_add &&
	       dev->xfrmdev_ops->xdo_dev_state_delete)))
		return NOTIFY_BAD;
#else
	if (dev->features & (NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM))
		return NOTIFY_BAD;
#endif

	return NOTIFY_DONE;
}