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
typedef  size_t u8 ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct ipv6hdr {size_t nexthdr; } ;
struct inet6_protocol {int /*<<< orphan*/  (* err_handler ) (struct sk_buff*,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_MIB_INERRORS ; 
 int /*<<< orphan*/  __ICMP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __in6_dev_get (int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet6_protos ; 
 scalar_t__ ipv6_ext_hdr (size_t) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  raw6_icmp_error (struct sk_buff*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 struct inet6_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ) ; 

void icmpv6_notify(struct sk_buff *skb, u8 type, u8 code, __be32 info)
{
	const struct inet6_protocol *ipprot;
	int inner_offset;
	__be16 frag_off;
	u8 nexthdr;
	struct net *net = dev_net(skb->dev);

	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr)))
		goto out;

	nexthdr = ((struct ipv6hdr *)skb->data)->nexthdr;
	if (ipv6_ext_hdr(nexthdr)) {
		/* now skip over extension headers */
		inner_offset = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr),
						&nexthdr, &frag_off);
		if (inner_offset < 0)
			goto out;
	} else {
		inner_offset = sizeof(struct ipv6hdr);
	}

	/* Checkin header including 8 bytes of inner protocol header. */
	if (!pskb_may_pull(skb, inner_offset+8))
		goto out;

	/* BUGGG_FUTURE: we should try to parse exthdrs in this packet.
	   Without this we will not able f.e. to make source routed
	   pmtu discovery.
	   Corresponding argument (opt) to notifiers is already added.
	   --ANK (980726)
	 */

	ipprot = rcu_dereference(inet6_protos[nexthdr]);
	if (ipprot && ipprot->err_handler)
		ipprot->err_handler(skb, NULL, type, code, inner_offset, info);

	raw6_icmp_error(skb, nexthdr, type, code, inner_offset, info);
	return;

out:
	__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev), ICMP6_MIB_INERRORS);
}