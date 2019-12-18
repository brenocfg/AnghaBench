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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct batadv_priv {struct net_device* soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  batadv_mcast_mla_rtr_flags_softif_get_ipv4 (struct net_device*) ; 
 int /*<<< orphan*/  batadv_mcast_mla_rtr_flags_softif_get_ipv6 (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static u8 batadv_mcast_mla_rtr_flags_softif_get(struct batadv_priv *bat_priv,
						struct net_device *bridge)
{
	struct net_device *dev = bridge ? bridge : bat_priv->soft_iface;
	u8 flags = BATADV_NO_FLAGS;

	rcu_read_lock();

	flags |= batadv_mcast_mla_rtr_flags_softif_get_ipv4(dev);
	flags |= batadv_mcast_mla_rtr_flags_softif_get_ipv6(dev);

	rcu_read_unlock();

	return flags;
}