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
struct nf_hook_state {int /*<<< orphan*/  sk; int /*<<< orphan*/  net; int /*<<< orphan*/  (* okfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct nf_bridge_info {int /*<<< orphan*/  in_prerouting; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  netif_is_l3_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_is_l3_slave (int /*<<< orphan*/ ) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static unsigned int ip_sabotage_in(void *priv,
				   struct sk_buff *skb,
				   const struct nf_hook_state *state)
{
	struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	if (nf_bridge && !nf_bridge->in_prerouting &&
	    !netif_is_l3_master(skb->dev) &&
	    !netif_is_l3_slave(skb->dev)) {
		state->okfn(state->net, state->sk, skb);
		return NF_STOLEN;
	}

	return NF_ACCEPT;
}