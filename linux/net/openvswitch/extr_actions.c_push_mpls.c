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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mac_len; } ;
struct ovs_action_push_mpls {int /*<<< orphan*/  mpls_ethertype; int /*<<< orphan*/  mpls_lse; } ;

/* Variables and functions */
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int skb_mpls_push (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_mpls(struct sk_buff *skb, struct sw_flow_key *key,
		     const struct ovs_action_push_mpls *mpls)
{
	int err;

	err = skb_mpls_push(skb, mpls->mpls_lse, mpls->mpls_ethertype,
			    skb->mac_len);
	if (err)
		return err;

	invalidate_flow_key(key);
	return 0;
}