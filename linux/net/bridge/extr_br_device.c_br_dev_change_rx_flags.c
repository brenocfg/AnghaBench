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

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  br_manage_promisc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static void br_dev_change_rx_flags(struct net_device *dev, int change)
{
	if (change & IFF_PROMISC)
		br_manage_promisc(netdev_priv(dev));
}