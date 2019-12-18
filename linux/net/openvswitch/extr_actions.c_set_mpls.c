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
struct TYPE_2__ {int /*<<< orphan*/  top_lse; } ;
struct sw_flow_key {TYPE_1__ mpls; } ;
struct sk_buff {int dummy; } ;
struct mpls_shim_hdr {int /*<<< orphan*/  label_stack_entry; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 struct mpls_shim_hdr* mpls_hdr (struct sk_buff*) ; 
 int skb_mpls_update_lse (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_mpls(struct sk_buff *skb, struct sw_flow_key *flow_key,
		    const __be32 *mpls_lse, const __be32 *mask)
{
	struct mpls_shim_hdr *stack;
	__be32 lse;
	int err;

	stack = mpls_hdr(skb);
	lse = OVS_MASKED(stack->label_stack_entry, *mpls_lse, *mask);
	err = skb_mpls_update_lse(skb, lse);
	if (err)
		return err;

	flow_key->mpls.top_lse = lse;
	return 0;
}