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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ipv6_txoptions {scalar_t__ dst1opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXTHDR_DEST ; 
 int /*<<< orphan*/  ipv6_push_exthdr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void ipv6_push_frag_opts(struct sk_buff *skb, struct ipv6_txoptions *opt, u8 *proto)
{
	if (opt->dst1opt)
		ipv6_push_exthdr(skb, proto, NEXTHDR_DEST, opt->dst1opt);
}