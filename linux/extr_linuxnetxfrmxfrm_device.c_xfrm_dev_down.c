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
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  xfrm_dev_state_flush (int /*<<< orphan*/ ,struct net_device*,int) ; 

__attribute__((used)) static int xfrm_dev_down(struct net_device *dev)
{
	if (dev->features & NETIF_F_HW_ESP)
		xfrm_dev_state_flush(dev_net(dev), dev, true);

	return NOTIFY_DONE;
}