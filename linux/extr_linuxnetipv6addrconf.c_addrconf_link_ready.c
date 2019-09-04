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
 scalar_t__ netif_oper_up (struct net_device const*) ; 
 int /*<<< orphan*/  qdisc_tx_is_noop (struct net_device const*) ; 

__attribute__((used)) static inline bool addrconf_link_ready(const struct net_device *dev)
{
	return netif_oper_up(dev) && !qdisc_tx_is_noop(dev);
}