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
struct net {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_ifindex; scalar_t__* ifr_name; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int netdev_get_name (struct net*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_ifname(struct net *net, struct ifreq *ifr)
{
	ifr->ifr_name[IFNAMSIZ-1] = 0;
	return netdev_get_name(net, ifr->ifr_name, ifr->ifr_ifindex);
}