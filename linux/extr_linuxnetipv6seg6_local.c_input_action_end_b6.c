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
struct sk_buff {scalar_t__ len; } ;
struct seg6_local_lwt {int /*<<< orphan*/  srh; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_sr_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int dst_input (struct sk_buff*) ; 
 struct ipv6_sr_hdr* get_and_validate_srh (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int seg6_do_srh_inline (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seg6_lookup_nexthop (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 

__attribute__((used)) static int input_action_end_b6(struct sk_buff *skb, struct seg6_local_lwt *slwt)
{
	struct ipv6_sr_hdr *srh;
	int err = -EINVAL;

	srh = get_and_validate_srh(skb);
	if (!srh)
		goto drop;

	err = seg6_do_srh_inline(skb, slwt->srh);
	if (err)
		goto drop;

	ipv6_hdr(skb)->payload_len = htons(skb->len - sizeof(struct ipv6hdr));
	skb_set_transport_header(skb, sizeof(struct ipv6hdr));

	seg6_lookup_nexthop(skb, NULL, 0);

	return dst_input(skb);

drop:
	kfree_skb(skb);
	return err;
}