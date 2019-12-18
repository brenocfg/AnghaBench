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
struct nf_hook_state {int dummy; } ;

/* Variables and functions */
 int NF_ACCEPT ; 
 int nf_ct_bridge_confirm (struct sk_buff*) ; 
 unsigned int nf_ct_bridge_refrag (struct sk_buff*,struct nf_hook_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_bridge_refrag_post ; 

__attribute__((used)) static unsigned int nf_ct_bridge_post(void *priv, struct sk_buff *skb,
				      const struct nf_hook_state *state)
{
	int ret;

	ret = nf_ct_bridge_confirm(skb);
	if (ret != NF_ACCEPT)
		return ret;

	return nf_ct_bridge_refrag(skb, state, nf_ct_bridge_refrag_post);
}