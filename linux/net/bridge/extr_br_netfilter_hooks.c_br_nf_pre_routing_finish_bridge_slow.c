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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct nf_bridge_info {int /*<<< orphan*/ * physoutdev; int /*<<< orphan*/  physindev; int /*<<< orphan*/  neigh_header; scalar_t__ bridged_dnat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  br_handle_frame_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void br_nf_pre_routing_finish_bridge_slow(struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	skb_pull(skb, ETH_HLEN);
	nf_bridge->bridged_dnat = 0;

	BUILD_BUG_ON(sizeof(nf_bridge->neigh_header) != (ETH_HLEN - ETH_ALEN));

	skb_copy_to_linear_data_offset(skb, -(ETH_HLEN - ETH_ALEN),
				       nf_bridge->neigh_header,
				       ETH_HLEN - ETH_ALEN);
	skb->dev = nf_bridge->physindev;

	nf_bridge->physoutdev = NULL;
	br_handle_frame_finish(dev_net(skb->dev), NULL, skb);
}