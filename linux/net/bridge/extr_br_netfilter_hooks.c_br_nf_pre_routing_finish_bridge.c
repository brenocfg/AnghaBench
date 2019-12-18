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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct nf_bridge_info {int bridged_dnat; int /*<<< orphan*/  neigh_header; int /*<<< orphan*/  physindev; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ hh_len; } ;
struct neighbour {int nud_state; int (* output ) (struct neighbour*,struct sk_buff*) ;TYPE_1__ hh; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int NUD_CONNECTED ; 
 int br_handle_frame_finish (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  bridge_parent (int /*<<< orphan*/ ) ; 
 struct neighbour* dst_neigh_lookup_skb (struct dst_entry*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_hh_bridge (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct neighbour*,struct sk_buff*) ; 

int br_nf_pre_routing_finish_bridge(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct neighbour *neigh;
	struct dst_entry *dst;

	skb->dev = bridge_parent(skb->dev);
	if (!skb->dev)
		goto free_skb;
	dst = skb_dst(skb);
	neigh = dst_neigh_lookup_skb(dst, skb);
	if (neigh) {
		struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
		int ret;

		if ((neigh->nud_state & NUD_CONNECTED) && neigh->hh.hh_len) {
			neigh_hh_bridge(&neigh->hh, skb);
			skb->dev = nf_bridge->physindev;
			ret = br_handle_frame_finish(net, sk, skb);
		} else {
			/* the neighbour function below overwrites the complete
			 * MAC header, so we save the Ethernet source address and
			 * protocol number.
			 */
			skb_copy_from_linear_data_offset(skb,
							 -(ETH_HLEN-ETH_ALEN),
							 nf_bridge->neigh_header,
							 ETH_HLEN-ETH_ALEN);
			/* tell br_dev_xmit to continue with forwarding */
			nf_bridge->bridged_dnat = 1;
			/* FIXME Need to refragment */
			ret = neigh->output(neigh, skb);
		}
		neigh_release(neigh);
		return ret;
	}
free_skb:
	kfree_skb(skb);
	return 0;
}