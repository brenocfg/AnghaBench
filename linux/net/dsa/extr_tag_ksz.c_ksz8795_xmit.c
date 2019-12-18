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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSZ8795_INGRESS_TAG_LEN ; 
 int KSZ8795_TAIL_TAG_OVERRIDE ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 scalar_t__ is_link_local_ether_addr (int*) ; 
 struct sk_buff* ksz_common_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int* skb_mac_header (struct sk_buff*) ; 
 int* skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ksz8795_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct sk_buff *nskb;
	u8 *tag;
	u8 *addr;

	nskb = ksz_common_xmit(skb, dev, KSZ8795_INGRESS_TAG_LEN);
	if (!nskb)
		return NULL;

	/* Tag encoding */
	tag = skb_put(nskb, KSZ8795_INGRESS_TAG_LEN);
	addr = skb_mac_header(nskb);

	*tag = 1 << dp->index;
	if (is_link_local_ether_addr(addr))
		*tag |= KSZ8795_TAIL_TAG_OVERRIDE;

	return nskb;
}