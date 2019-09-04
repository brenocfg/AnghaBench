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
typedef  int u8 ;
struct sk_buff {int len; int /*<<< orphan*/  dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSZ_EGRESS_TAG_LEN ; 
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_trim_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *ksz_rcv(struct sk_buff *skb, struct net_device *dev,
			       struct packet_type *pt)
{
	u8 *tag;
	int source_port;

	tag = skb_tail_pointer(skb) - KSZ_EGRESS_TAG_LEN;

	source_port = tag[0] & 7;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	if (!skb->dev)
		return NULL;

	pskb_trim_rcsum(skb, skb->len - KSZ_EGRESS_TAG_LEN);

	return skb;
}