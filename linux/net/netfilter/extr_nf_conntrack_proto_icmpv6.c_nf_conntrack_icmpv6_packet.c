#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valid_new ;
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {scalar_t__ pf; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_6__ {int type; } ;
struct TYPE_7__ {TYPE_1__ icmp; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ dst; } ;
struct TYPE_9__ {TYPE_5__ tuple; } ;

/* Variables and functions */
#define  ICMPV6_ECHO_REQUEST 129 
#define  ICMPV6_NI_QUERY 128 
 scalar_t__ NFPROTO_IPV6 ; 
 int NF_ACCEPT ; 
 unsigned int* icmpv6_get_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_dump_tuple_ipv6 (TYPE_5__*) ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff*,unsigned int) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int nf_conntrack_icmpv6_packet(struct nf_conn *ct,
			       struct sk_buff *skb,
			       enum ip_conntrack_info ctinfo,
			       const struct nf_hook_state *state)
{
	unsigned int *timeout = nf_ct_timeout_lookup(ct);
	static const u8 valid_new[] = {
		[ICMPV6_ECHO_REQUEST - 128] = 1,
		[ICMPV6_NI_QUERY - 128] = 1
	};

	if (state->pf != NFPROTO_IPV6)
		return -NF_ACCEPT;

	if (!nf_ct_is_confirmed(ct)) {
		int type = ct->tuplehash[0].tuple.dst.u.icmp.type - 128;

		if (type < 0 || type >= sizeof(valid_new) || !valid_new[type]) {
			/* Can't create a new ICMPv6 `conn' with this. */
			pr_debug("icmpv6: can't create new conn with type %u\n",
				 type + 128);
			nf_ct_dump_tuple_ipv6(&ct->tuplehash[0].tuple);
			return -NF_ACCEPT;
		}
	}

	if (!timeout)
		timeout = icmpv6_get_timeouts(nf_ct_net(ct));

	/* Do not immediately delete the connection after the first
	   successful reply to avoid excessive conntrackd traffic
	   and also to handle correctly ICMP echo reply duplicates. */
	nf_ct_refresh_acct(ct, ctinfo, skb, *timeout);

	return NF_ACCEPT;
}