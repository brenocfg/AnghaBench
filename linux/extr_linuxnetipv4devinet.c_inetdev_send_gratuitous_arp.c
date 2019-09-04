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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; struct in_ifaddr* ifa_next; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  arp_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inetdev_send_gratuitous_arp(struct net_device *dev,
					struct in_device *in_dev)

{
	struct in_ifaddr *ifa;

	for (ifa = in_dev->ifa_list; ifa;
	     ifa = ifa->ifa_next) {
		arp_send(ARPOP_REQUEST, ETH_P_ARP,
			 ifa->ifa_local, dev,
			 ifa->ifa_local, NULL,
			 dev->dev_addr, NULL);
	}
}