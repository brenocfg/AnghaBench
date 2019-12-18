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
typedef  int /*<<< orphan*/  u16 ;
struct vport {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  inner_protocol; int /*<<< orphan*/  _skb_refdst; } ;
struct ovs_frag_data {int vlan_tci; unsigned int l2_len; int /*<<< orphan*/  l2_data; int /*<<< orphan*/  mac_proto; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  network_offset; int /*<<< orphan*/  inner_protocol; int /*<<< orphan*/  cb; struct vport* vport; int /*<<< orphan*/  dst; } ;
struct inet_skb_parm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/ * OVS_CB (struct sk_buff*) ; 
 int VLAN_CFI_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ovs_frag_data_storage ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 struct ovs_frag_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_frag(struct vport *vport, struct sk_buff *skb,
			 u16 orig_network_offset, u8 mac_proto)
{
	unsigned int hlen = skb_network_offset(skb);
	struct ovs_frag_data *data;

	data = this_cpu_ptr(&ovs_frag_data_storage);
	data->dst = skb->_skb_refdst;
	data->vport = vport;
	data->cb = *OVS_CB(skb);
	data->inner_protocol = skb->inner_protocol;
	data->network_offset = orig_network_offset;
	if (skb_vlan_tag_present(skb))
		data->vlan_tci = skb_vlan_tag_get(skb) | VLAN_CFI_MASK;
	else
		data->vlan_tci = 0;
	data->vlan_proto = skb->vlan_proto;
	data->mac_proto = mac_proto;
	data->l2_len = hlen;
	memcpy(&data->l2_data, skb->data, hlen);

	memset(IPCB(skb), 0, sizeof(struct inet_skb_parm));
	skb_pull(skb, hlen);
}