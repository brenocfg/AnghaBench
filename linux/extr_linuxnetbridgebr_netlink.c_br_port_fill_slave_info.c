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
struct net_device {int dummy; } ;

/* Variables and functions */
 int br_port_fill_attrs (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_port_get_rtnl (struct net_device const*) ; 

__attribute__((used)) static int br_port_fill_slave_info(struct sk_buff *skb,
				   const struct net_device *brdev,
				   const struct net_device *dev)
{
	return br_port_fill_attrs(skb, br_port_get_rtnl(dev));
}