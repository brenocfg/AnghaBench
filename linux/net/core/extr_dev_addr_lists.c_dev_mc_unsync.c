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
struct net_device {scalar_t__ addr_len; int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  __hw_addr_unsync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_addr_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 

void dev_mc_unsync(struct net_device *to, struct net_device *from)
{
	if (to->addr_len != from->addr_len)
		return;

	netif_addr_lock_bh(from);
	netif_addr_lock(to);
	__hw_addr_unsync(&to->mc, &from->mc, to->addr_len);
	__dev_set_rx_mode(to);
	netif_addr_unlock(to);
	netif_addr_unlock_bh(from);
}