#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_hook_state {scalar_t__ pf; } ;
struct TYPE_3__ {unsigned int stream_timeout; unsigned int timeout; } ;
struct TYPE_4__ {TYPE_1__ gre; } ;
struct nf_conn {int status; TYPE_2__ proto; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 size_t GRE_CT_REPLIED ; 
 size_t GRE_CT_UNREPLIED ; 
 int /*<<< orphan*/  IPCT_ASSURED ; 
 int /*<<< orphan*/  IPS_ASSURED_BIT ; 
 int IPS_SEEN_REPLY ; 
 scalar_t__ NFPROTO_IPV4 ; 
 int NF_ACCEPT ; 
 unsigned int* gre_get_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff*,unsigned int) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int*) ; 

int nf_conntrack_gre_packet(struct nf_conn *ct,
			    struct sk_buff *skb,
			    unsigned int dataoff,
			    enum ip_conntrack_info ctinfo,
			    const struct nf_hook_state *state)
{
	if (state->pf != NFPROTO_IPV4)
		return -NF_ACCEPT;

	if (!nf_ct_is_confirmed(ct)) {
		unsigned int *timeouts = nf_ct_timeout_lookup(ct);

		if (!timeouts)
			timeouts = gre_get_timeouts(nf_ct_net(ct));

		/* initialize to sane value.  Ideally a conntrack helper
		 * (e.g. in case of pptp) is increasing them */
		ct->proto.gre.stream_timeout = timeouts[GRE_CT_REPLIED];
		ct->proto.gre.timeout = timeouts[GRE_CT_UNREPLIED];
	}

	/* If we've seen traffic both ways, this is a GRE connection.
	 * Extend timeout. */
	if (ct->status & IPS_SEEN_REPLY) {
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   ct->proto.gre.stream_timeout);
		/* Also, more likely to be important, and not a probe. */
		if (!test_and_set_bit(IPS_ASSURED_BIT, &ct->status))
			nf_conntrack_event_cache(IPCT_ASSURED, ct);
	} else
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   ct->proto.gre.timeout);

	return NF_ACCEPT;
}