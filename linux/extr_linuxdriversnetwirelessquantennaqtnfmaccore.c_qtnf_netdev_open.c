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
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_netdev_updown (struct net_device*,int) ; 

__attribute__((used)) static int qtnf_netdev_open(struct net_device *ndev)
{
	netif_carrier_off(ndev);
	qtnf_netdev_updown(ndev, 1);
	return 0;
}