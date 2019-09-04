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
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int NF_ACCEPT ; 
 unsigned int* icmpv6_get_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff const*,unsigned int) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 

__attribute__((used)) static int icmpv6_packet(struct nf_conn *ct,
		       const struct sk_buff *skb,
		       unsigned int dataoff,
		       enum ip_conntrack_info ctinfo)
{
	unsigned int *timeout = nf_ct_timeout_lookup(ct);

	if (!timeout)
		timeout = icmpv6_get_timeouts(nf_ct_net(ct));

	/* Do not immediately delete the connection after the first
	   successful reply to avoid excessive conntrackd traffic
	   and also to handle correctly ICMP echo reply duplicates. */
	nf_ct_refresh_acct(ct, ctinfo, skb, *timeout);

	return NF_ACCEPT;
}