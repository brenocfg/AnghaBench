#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct vport {TYPE_2__* dev; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct sw_flow_key {TYPE_1__ eth; } ;
struct sk_buff {unsigned long _skb_refdst; int /*<<< orphan*/  sk; int /*<<< orphan*/  inner_network_header; int /*<<< orphan*/  network_header; int /*<<< orphan*/  protocol; } ;
struct dst_entry {TYPE_2__* dev; } ;
struct rt6_info {struct dst_entry dst; } ;
struct nf_ipv6_ops {int /*<<< orphan*/  (* fragment ) (struct net*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ;} ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  ovs_rt ;
struct TYPE_8__ {void* frag_max_size; } ;
struct TYPE_7__ {void* frag_max_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_NOCOUNT ; 
 int /*<<< orphan*/  DST_OBSOLETE_NONE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_4__* IP6CB (struct sk_buff*) ; 
 TYPE_3__* IPCB (struct sk_buff*) ; 
 scalar_t__ MAX_L2_LEN ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_init (struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_p_mpls (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_do_fragment (struct net*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct rt6_info*,int /*<<< orphan*/ ,int) ; 
 struct nf_ipv6_ops* nf_get_ipv6_ops () ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  ovs_dst_ops ; 
 int /*<<< orphan*/  ovs_key_mac_proto (struct sw_flow_key*) ; 
 int /*<<< orphan*/  ovs_vport_name (struct vport*) ; 
 int /*<<< orphan*/  ovs_vport_output ; 
 int /*<<< orphan*/  prepare_frag (struct vport*,struct sk_buff*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refdst_drop (unsigned long) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct net*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ovs_fragment(struct net *net, struct vport *vport,
			 struct sk_buff *skb, u16 mru,
			 struct sw_flow_key *key)
{
	u16 orig_network_offset = 0;

	if (eth_p_mpls(skb->protocol)) {
		orig_network_offset = skb_network_offset(skb);
		skb->network_header = skb->inner_network_header;
	}

	if (skb_network_offset(skb) > MAX_L2_LEN) {
		OVS_NLERR(1, "L2 header too long to fragment");
		goto err;
	}

	if (key->eth.type == htons(ETH_P_IP)) {
		struct dst_entry ovs_dst;
		unsigned long orig_dst;

		prepare_frag(vport, skb, orig_network_offset,
			     ovs_key_mac_proto(key));
		dst_init(&ovs_dst, &ovs_dst_ops, NULL, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		ovs_dst.dev = vport->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &ovs_dst);
		IPCB(skb)->frag_max_size = mru;

		ip_do_fragment(net, skb->sk, skb, ovs_vport_output);
		refdst_drop(orig_dst);
	} else if (key->eth.type == htons(ETH_P_IPV6)) {
		const struct nf_ipv6_ops *v6ops = nf_get_ipv6_ops();
		unsigned long orig_dst;
		struct rt6_info ovs_rt;

		if (!v6ops)
			goto err;

		prepare_frag(vport, skb, orig_network_offset,
			     ovs_key_mac_proto(key));
		memset(&ovs_rt, 0, sizeof(ovs_rt));
		dst_init(&ovs_rt.dst, &ovs_dst_ops, NULL, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		ovs_rt.dst.dev = vport->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &ovs_rt.dst);
		IP6CB(skb)->frag_max_size = mru;

		v6ops->fragment(net, skb->sk, skb, ovs_vport_output);
		refdst_drop(orig_dst);
	} else {
		WARN_ONCE(1, "Failed fragment ->%s: eth=%04x, MRU=%d, MTU=%d.",
			  ovs_vport_name(vport), ntohs(key->eth.type), mru,
			  vport->dev->mtu);
		goto err;
	}

	return;
err:
	kfree_skb(skb);
}