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
struct sk_buff {unsigned int len; scalar_t__ protocol; } ;
struct mtk_eth {TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ padding_64b; int /*<<< orphan*/  padding_bug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 unsigned int ETH_ZLEN ; 
 unsigned int VLAN_ETH_ZLEN ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int skb_pad (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_skb_padto(struct sk_buff *skb, struct mtk_eth *eth)
{
	unsigned int len;
	int ret;

	if (unlikely(skb->len >= VLAN_ETH_ZLEN))
		return 0;

	if (eth->soc->padding_64b && !eth->soc->padding_bug)
		return 0;

	if (skb_vlan_tag_present(skb))
		len = ETH_ZLEN;
	else if (skb->protocol == cpu_to_be16(ETH_P_8021Q))
		len = VLAN_ETH_ZLEN;
	else if (!eth->soc->padding_64b)
		len = ETH_ZLEN;
	else
		return 0;

	if (skb->len >= len)
		return 0;

	ret = skb_pad(skb, len - skb->len);
	if (ret < 0)
		return ret;
	skb->len = len;
	skb_set_tail_pointer(skb, len);

	return ret;
}