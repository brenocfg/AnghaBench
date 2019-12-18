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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct brnf_frag_data {int /*<<< orphan*/  encap_size; int /*<<< orphan*/  size; int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan_tci; scalar_t__ vlan_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int br_dev_queue_push_xmit (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  brnf_frag_data_storage ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_info_free (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct brnf_frag_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_nf_push_frag_xmit(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct brnf_frag_data *data;
	int err;

	data = this_cpu_ptr(&brnf_frag_data_storage);
	err = skb_cow_head(skb, data->size);

	if (err) {
		kfree_skb(skb);
		return 0;
	}

	if (data->vlan_proto)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci);

	skb_copy_to_linear_data_offset(skb, -data->size, data->mac, data->size);
	__skb_push(skb, data->encap_size);

	nf_bridge_info_free(skb);
	return br_dev_queue_push_xmit(net, sk, skb);
}