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
struct sk_buff {int dummy; } ;
struct nf_bridge_frag_data {int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  vlan_proto; scalar_t__ vlan_present; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int nf_ct_bridge_frag_restore(struct sk_buff *skb,
				     const struct nf_bridge_frag_data *data)
{
	int err;

	err = skb_cow_head(skb, ETH_HLEN);
	if (err) {
		kfree_skb(skb);
		return -ENOMEM;
	}
	if (data->vlan_present)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci);
	else if (skb_vlan_tag_present(skb))
		__vlan_hwaccel_clear_tag(skb);

	skb_copy_to_linear_data_offset(skb, -ETH_HLEN, data->mac, ETH_HLEN);
	skb_reset_mac_header(skb);

	return 0;
}