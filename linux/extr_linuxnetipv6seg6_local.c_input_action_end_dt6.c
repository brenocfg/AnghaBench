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
struct seg6_local_lwt {int /*<<< orphan*/  table; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  decap_and_validate (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dst_input (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  seg6_lookup_nexthop (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int input_action_end_dt6(struct sk_buff *skb,
				struct seg6_local_lwt *slwt)
{
	if (!decap_and_validate(skb, IPPROTO_IPV6))
		goto drop;

	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr)))
		goto drop;

	seg6_lookup_nexthop(skb, NULL, slwt->table);

	return dst_input(skb);

drop:
	kfree_skb(skb);
	return -EINVAL;
}