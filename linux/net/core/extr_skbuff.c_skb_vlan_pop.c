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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int __skb_vlan_pop (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_vlan (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int skb_vlan_pop(struct sk_buff *skb)
{
	u16 vlan_tci;
	__be16 vlan_proto;
	int err;

	if (likely(skb_vlan_tag_present(skb))) {
		__vlan_hwaccel_clear_tag(skb);
	} else {
		if (unlikely(!eth_type_vlan(skb->protocol)))
			return 0;

		err = __skb_vlan_pop(skb, &vlan_tci);
		if (err)
			return err;
	}
	/* move next vlan tag to hw accel tag */
	if (likely(!eth_type_vlan(skb->protocol)))
		return 0;

	vlan_proto = skb->protocol;
	err = __skb_vlan_pop(skb, &vlan_tci);
	if (unlikely(err))
		return err;

	__vlan_hwaccel_put_tag(skb, vlan_proto, vlan_tci);
	return 0;
}