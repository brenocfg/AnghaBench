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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_scrub_packet (struct sk_buff*,int) ; 

__attribute__((used)) static void ipvlan_skb_crossing_ns(struct sk_buff *skb, struct net_device *dev)
{
	bool xnet = true;

	if (dev)
		xnet = !net_eq(dev_net(skb->dev), dev_net(dev));

	skb_scrub_packet(skb, xnet);
	if (dev)
		skb->dev = dev;
}