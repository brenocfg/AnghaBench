#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct dsa_port {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 scalar_t__ QCA_HDR_LEN ; 
 int QCA_HDR_VERSION ; 
 int QCA_HDR_XMIT_FROM_CPU ; 
 int QCA_HDR_XMIT_VERSION_S ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int htons (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *qca_tag_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	u16 *phdr, hdr;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	if (skb_cow_head(skb, 0) < 0)
		return NULL;

	skb_push(skb, QCA_HDR_LEN);

	memmove(skb->data, skb->data + QCA_HDR_LEN, 2 * ETH_ALEN);
	phdr = (u16 *)(skb->data + 2 * ETH_ALEN);

	/* Set the version field, and set destination port information */
	hdr = QCA_HDR_VERSION << QCA_HDR_XMIT_VERSION_S |
		QCA_HDR_XMIT_FROM_CPU | BIT(dp->index);

	*phdr = htons(hdr);

	return skb;
}