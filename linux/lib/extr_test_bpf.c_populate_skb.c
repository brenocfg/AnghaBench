#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* dev; void* vlan_proto; int /*<<< orphan*/  vlan_present; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/  hash; int /*<<< orphan*/  mark; int /*<<< orphan*/  pkt_type; void* protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_DATA ; 
 int /*<<< orphan*/  SKB_DEV_IFINDEX ; 
 int /*<<< orphan*/  SKB_DEV_TYPE ; 
 int /*<<< orphan*/  SKB_HASH ; 
 int /*<<< orphan*/  SKB_MARK ; 
 int /*<<< orphan*/  SKB_QUEUE_MAP ; 
 int /*<<< orphan*/  SKB_TYPE ; 
 int /*<<< orphan*/  SKB_VLAN_PRESENT ; 
 int /*<<< orphan*/  SKB_VLAN_TCI ; 
 int /*<<< orphan*/  __skb_put_data (struct sk_buff*,char*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  dev_net_set (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *populate_skb(char *buf, int size)
{
	struct sk_buff *skb;

	if (size >= MAX_DATA)
		return NULL;

	skb = alloc_skb(MAX_DATA, GFP_KERNEL);
	if (!skb)
		return NULL;

	__skb_put_data(skb, buf, size);

	/* Initialize a fake skb with test pattern. */
	skb_reset_mac_header(skb);
	skb->protocol = htons(ETH_P_IP);
	skb->pkt_type = SKB_TYPE;
	skb->mark = SKB_MARK;
	skb->hash = SKB_HASH;
	skb->queue_mapping = SKB_QUEUE_MAP;
	skb->vlan_tci = SKB_VLAN_TCI;
	skb->vlan_present = SKB_VLAN_PRESENT;
	skb->vlan_proto = htons(ETH_P_IP);
	dev_net_set(&dev, &init_net);
	skb->dev = &dev;
	skb->dev->ifindex = SKB_DEV_IFINDEX;
	skb->dev->type = SKB_DEV_TYPE;
	skb_set_network_header(skb, min(size, ETH_HLEN));

	return skb;
}