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
struct ipv6_opt_hdr {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  memcpy (struct ipv6_opt_hdr*,struct ipv6_opt_hdr*,int /*<<< orphan*/ ) ; 
 struct ipv6_opt_hdr* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipv6_push_exthdr(struct sk_buff *skb, u8 *proto, u8 type, struct ipv6_opt_hdr *opt)
{
	struct ipv6_opt_hdr *h = skb_push(skb, ipv6_optlen(opt));

	memcpy(h, opt, ipv6_optlen(opt));
	h->nexthdr = *proto;
	*proto = type;
}