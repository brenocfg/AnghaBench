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
struct sock {int /*<<< orphan*/  sk_v6_daddr; } ;
struct sk_buff {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  saddr; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_csum_outgoing (struct sk_buff*) ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v6_csum_finish (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 

__attribute__((used)) static inline void dccp_v6_send_check(struct sock *sk, struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct dccp_hdr *dh = dccp_hdr(skb);

	dccp_csum_outgoing(skb);
	dh->dccph_checksum = dccp_v6_csum_finish(skb, &np->saddr, &sk->sk_v6_daddr);
}