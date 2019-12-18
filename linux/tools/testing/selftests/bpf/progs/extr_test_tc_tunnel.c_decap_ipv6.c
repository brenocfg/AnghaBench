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
struct ipv6hdr {int /*<<< orphan*/  nexthdr; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  iph_outer ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int TC_ACT_OK ; 
 scalar_t__ bpf_skb_load_bytes (struct __sk_buff*,int /*<<< orphan*/ ,struct ipv6hdr*,int) ; 
 int decap_internal (struct __sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decap_ipv6(struct __sk_buff *skb)
{
	struct ipv6hdr iph_outer;

	if (bpf_skb_load_bytes(skb, ETH_HLEN, &iph_outer,
			       sizeof(iph_outer)) < 0)
		return TC_ACT_OK;

	return decap_internal(skb, ETH_HLEN, sizeof(iph_outer),
			      iph_outer.nexthdr);
}