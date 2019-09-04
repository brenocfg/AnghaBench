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
struct net_device {int hard_header_len; int addr_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_DLCI ; 
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void pvc_setup(struct net_device *dev)
{
	dev->type = ARPHRD_DLCI;
	dev->flags = IFF_POINTOPOINT;
	dev->hard_header_len = 10;
	dev->addr_len = 2;
	netif_keep_dst(dev);
}