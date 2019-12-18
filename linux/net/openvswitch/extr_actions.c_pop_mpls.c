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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int skb_mpls_pop (struct sk_buff*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pop_mpls(struct sk_buff *skb, struct sw_flow_key *key,
		    const __be16 ethertype)
{
	int err;

	err = skb_mpls_pop(skb, ethertype, skb->mac_len);
	if (err)
		return err;

	invalidate_flow_key(key);
	return 0;
}