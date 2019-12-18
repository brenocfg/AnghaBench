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
struct vlan_head {int tci; int /*<<< orphan*/  tpid; } ;
struct sk_buff {int data; int len; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VLAN_CFI_MASK ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int __skb_vlan_pop (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_vlan (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int skb_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_vlan_tag(struct sk_buff *skb, struct vlan_head *key_vh,
			  bool untag_vlan)
{
	struct vlan_head *vh = (struct vlan_head *)skb->data;

	if (likely(!eth_type_vlan(vh->tpid)))
		return 0;

	if (unlikely(skb->len < sizeof(struct vlan_head) + sizeof(__be16)))
		return 0;

	if (unlikely(!pskb_may_pull(skb, sizeof(struct vlan_head) +
				 sizeof(__be16))))
		return -ENOMEM;

	vh = (struct vlan_head *)skb->data;
	key_vh->tci = vh->tci | htons(VLAN_CFI_MASK);
	key_vh->tpid = vh->tpid;

	if (unlikely(untag_vlan)) {
		int offset = skb->data - skb_mac_header(skb);
		u16 tci;
		int err;

		__skb_push(skb, offset);
		err = __skb_vlan_pop(skb, &tci);
		__skb_pull(skb, offset);
		if (err)
			return err;
		__vlan_hwaccel_put_tag(skb, key_vh->tpid, tci);
	} else {
		__skb_pull(skb, sizeof(struct vlan_head));
	}
	return 1;
}