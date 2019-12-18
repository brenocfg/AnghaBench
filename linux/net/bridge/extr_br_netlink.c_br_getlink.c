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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct net_bridge_port {int dummy; } ;

/* Variables and functions */
 int RTEXT_FILTER_BRVLAN ; 
 int RTEXT_FILTER_BRVLAN_COMPRESSED ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int br_fill_ifinfo (struct sk_buff*,struct net_bridge_port*,int,int,int /*<<< orphan*/ ,int,int,struct net_device*) ; 
 struct net_bridge_port* br_port_get_rtnl (struct net_device*) ; 

int br_getlink(struct sk_buff *skb, u32 pid, u32 seq,
	       struct net_device *dev, u32 filter_mask, int nlflags)
{
	struct net_bridge_port *port = br_port_get_rtnl(dev);

	if (!port && !(filter_mask & RTEXT_FILTER_BRVLAN) &&
	    !(filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED))
		return 0;

	return br_fill_ifinfo(skb, port, pid, seq, RTM_NEWLINK, nlflags,
			      filter_mask, dev);
}