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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dsa_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_port_is_vlan_filtering (int /*<<< orphan*/ ) ; 
 scalar_t__ sja1105_is_link_local (struct sk_buff const*) ; 
 scalar_t__ sja1105_is_meta_frame (struct sk_buff const*) ; 

__attribute__((used)) static bool sja1105_filter(const struct sk_buff *skb, struct net_device *dev)
{
	if (!dsa_port_is_vlan_filtering(dev->dsa_ptr))
		return true;
	if (sja1105_is_link_local(skb))
		return true;
	if (sja1105_is_meta_frame(skb))
		return true;
	return false;
}