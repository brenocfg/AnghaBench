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
struct udphdr {scalar_t__ check; } ;
struct sk_buff {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int flush; int is_ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_gro_compute_pseudo ; 
 int /*<<< orphan*/  skb_gro_checksum_try_convert (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_gro_checksum_validate_zero_check (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp6_lib_lookup_skb ; 
 struct sk_buff* udp_gro_receive (struct list_head*,struct sk_buff*,struct udphdr*,int /*<<< orphan*/ ) ; 
 struct udphdr* udp_gro_udphdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *udp6_gro_receive(struct list_head *head,
					struct sk_buff *skb)
{
	struct udphdr *uh = udp_gro_udphdr(skb);

	if (unlikely(!uh))
		goto flush;

	/* Don't bother verifying checksum if we're going to flush anyway. */
	if (NAPI_GRO_CB(skb)->flush)
		goto skip;

	if (skb_gro_checksum_validate_zero_check(skb, IPPROTO_UDP, uh->check,
						 ip6_gro_compute_pseudo))
		goto flush;
	else if (uh->check)
		skb_gro_checksum_try_convert(skb, IPPROTO_UDP, uh->check,
					     ip6_gro_compute_pseudo);

skip:
	NAPI_GRO_CB(skb)->is_ipv6 = 1;
	return udp_gro_receive(head, skb, uh, udp6_lib_lookup_skb);

flush:
	NAPI_GRO_CB(skb)->flush = 1;
	return NULL;
}