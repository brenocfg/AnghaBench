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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KSZ9893_TAIL_TAG_OVERRIDE ; 
 int /*<<< orphan*/  KSZ_INGRESS_TAG_LEN ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 scalar_t__ is_link_local_ether_addr (int /*<<< orphan*/ *) ; 
 struct sk_buff* ksz_common_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ksz9893_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct sk_buff *nskb;
	u8 *addr;
	u8 *tag;

	nskb = ksz_common_xmit(skb, dev, KSZ_INGRESS_TAG_LEN);
	if (!nskb)
		return NULL;

	/* Tag encoding */
	tag = skb_put(nskb, KSZ_INGRESS_TAG_LEN);
	addr = skb_mac_header(nskb);

	*tag = BIT(dp->index);

	if (is_link_local_ether_addr(addr))
		*tag |= KSZ9893_TAIL_TAG_OVERRIDE;

	return nskb;
}