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
struct slip {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct slip* netdev_priv (struct net_device*) ; 
 int sl_realloc_bufs (struct slip*,int) ; 

__attribute__((used)) static int sl_change_mtu(struct net_device *dev, int new_mtu)
{
	struct slip *sl = netdev_priv(dev);

	return sl_realloc_bufs(sl, new_mtu);
}