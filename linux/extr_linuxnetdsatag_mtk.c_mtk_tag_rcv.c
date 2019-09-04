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
struct sk_buff {int data; int /*<<< orphan*/  dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int __be16 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int MTK_HDR_LEN ; 
 int MTK_HDR_RECV_SOURCE_PORT_MASK ; 
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *mtk_tag_rcv(struct sk_buff *skb, struct net_device *dev,
				   struct packet_type *pt)
{
	int port;
	__be16 *phdr, hdr;

	if (unlikely(!pskb_may_pull(skb, MTK_HDR_LEN)))
		return NULL;

	/* The MTK header is added by the switch between src addr
	 * and ethertype at this point, skb->data points to 2 bytes
	 * after src addr so header should be 2 bytes right before.
	 */
	phdr = (__be16 *)(skb->data - 2);
	hdr = ntohs(*phdr);

	/* Remove MTK tag and recalculate checksum. */
	skb_pull_rcsum(skb, MTK_HDR_LEN);

	memmove(skb->data - ETH_HLEN,
		skb->data - ETH_HLEN - MTK_HDR_LEN,
		2 * ETH_ALEN);

	/* Get source port information */
	port = (hdr & MTK_HDR_RECV_SOURCE_PORT_MASK);

	skb->dev = dsa_master_find_slave(dev, 0, port);
	if (!skb->dev)
		return NULL;

	return skb;
}