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
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_ASSURED ; 
 int /*<<< orphan*/  IPS_ASSURED_BIT ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 int NF_ACCEPT ; 
 size_t UDP_CT_REPLIED ; 
 size_t UDP_CT_UNREPLIED ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff const*,unsigned int) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int* udp_get_timeouts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp_packet(struct nf_conn *ct,
		      const struct sk_buff *skb,
		      unsigned int dataoff,
		      enum ip_conntrack_info ctinfo)
{
	unsigned int *timeouts;

	timeouts = nf_ct_timeout_lookup(ct);
	if (!timeouts)
		timeouts = udp_get_timeouts(nf_ct_net(ct));

	/* If we've seen traffic both ways, this is some kind of UDP
	   stream.  Extend timeout. */
	if (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) {
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   timeouts[UDP_CT_REPLIED]);
		/* Also, more likely to be important, and not a probe */
		if (!test_and_set_bit(IPS_ASSURED_BIT, &ct->status))
			nf_conntrack_event_cache(IPCT_ASSURED, ct);
	} else {
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   timeouts[UDP_CT_UNREPLIED]);
	}
	return NF_ACCEPT;
}