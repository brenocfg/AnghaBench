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
struct vport {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  network_header; int /*<<< orphan*/  inner_network_header; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; int /*<<< orphan*/  inner_protocol; } ;
struct ovs_frag_data {int vlan_tci; int /*<<< orphan*/  mac_proto; int /*<<< orphan*/  network_offset; int /*<<< orphan*/  l2_len; int /*<<< orphan*/  l2_data; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  inner_protocol; int /*<<< orphan*/  cb; int /*<<< orphan*/  dst; struct vport* vport; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * OVS_CB (struct sk_buff*) ; 
 int VLAN_CFI_MASK ; 
 int /*<<< orphan*/  __skb_dst_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_frag_data_storage ; 
 int /*<<< orphan*/  ovs_vport_send (struct vport*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ovs_frag_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovs_vport_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct ovs_frag_data *data = this_cpu_ptr(&ovs_frag_data_storage);
	struct vport *vport = data->vport;

	if (skb_cow_head(skb, data->l2_len) < 0) {
		kfree_skb(skb);
		return -ENOMEM;
	}

	__skb_dst_copy(skb, data->dst);
	*OVS_CB(skb) = data->cb;
	skb->inner_protocol = data->inner_protocol;
	if (data->vlan_tci & VLAN_CFI_MASK)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci & ~VLAN_CFI_MASK);
	else
		__vlan_hwaccel_clear_tag(skb);

	/* Reconstruct the MAC header.  */
	skb_push(skb, data->l2_len);
	memcpy(skb->data, &data->l2_data, data->l2_len);
	skb_postpush_rcsum(skb, skb->data, data->l2_len);
	skb_reset_mac_header(skb);

	if (eth_p_mpls(skb->protocol)) {
		skb->inner_network_header = skb->network_header;
		skb_set_network_header(skb, data->network_offset);
		skb_reset_mac_len(skb);
	}

	ovs_vport_send(vport, skb, data->mac_proto);
	return 0;
}