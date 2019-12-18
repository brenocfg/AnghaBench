#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union nf_inet_addr {int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {scalar_t__ pf; int /*<<< orphan*/  net; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {TYPE_3__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_4__ {union nf_inet_addr u3; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct TYPE_6__ {TYPE_2__ tuple; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IP_CT_DIR_REPLY ; 
 scalar_t__ IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int NF_ACCEPT ; 
 int NF_CT_DIRECTION (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ ,struct nf_conntrack_zone const*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,unsigned int,scalar_t__,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 struct nf_conntrack_zone* nf_ct_zone_tmpl (struct nf_conn*,struct sk_buff*,struct nf_conntrack_zone*) ; 
 int /*<<< orphan*/  nf_inet_addr_cmp (union nf_inet_addr*,union nf_inet_addr*) ; 
 int /*<<< orphan*/  nf_l4proto_log_invalid (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_nfct (struct sk_buff*) ; 

int nf_conntrack_inet_error(struct nf_conn *tmpl, struct sk_buff *skb,
			    unsigned int dataoff,
			    const struct nf_hook_state *state,
			    u8 l4proto, union nf_inet_addr *outer_daddr)
{
	struct nf_conntrack_tuple innertuple, origtuple;
	const struct nf_conntrack_tuple_hash *h;
	const struct nf_conntrack_zone *zone;
	enum ip_conntrack_info ctinfo;
	struct nf_conntrack_zone tmp;
	union nf_inet_addr *ct_daddr;
	enum ip_conntrack_dir dir;
	struct nf_conn *ct;

	WARN_ON(skb_nfct(skb));
	zone = nf_ct_zone_tmpl(tmpl, skb, &tmp);

	/* Are they talking about one of our connections? */
	if (!nf_ct_get_tuplepr(skb, dataoff,
			       state->pf, state->net, &origtuple))
		return -NF_ACCEPT;

	/* Ordinarily, we'd expect the inverted tupleproto, but it's
	   been preserved inside the ICMP. */
	if (!nf_ct_invert_tuple(&innertuple, &origtuple))
		return -NF_ACCEPT;

	h = nf_conntrack_find_get(state->net, zone, &innertuple);
	if (!h)
		return -NF_ACCEPT;

	/* Consider: A -> T (=This machine) -> B
	 *   Conntrack entry will look like this:
	 *      Original:  A->B
	 *      Reply:     B->T (SNAT case) OR A
	 *
	 * When this function runs, we got packet that looks like this:
	 * iphdr|icmphdr|inner_iphdr|l4header (tcp, udp, ..).
	 *
	 * Above nf_conntrack_find_get() makes lookup based on inner_hdr,
	 * so we should expect that destination of the found connection
	 * matches outer header destination address.
	 *
	 * In above example, we can consider these two cases:
	 *  1. Error coming in reply direction from B or M (middle box) to
	 *     T (SNAT case) or A.
	 *     Inner saddr will be B, dst will be T or A.
	 *     The found conntrack will be reply tuple (B->T/A).
	 *  2. Error coming in original direction from A or M to B.
	 *     Inner saddr will be A, inner daddr will be B.
	 *     The found conntrack will be original tuple (A->B).
	 *
	 * In both cases, conntrack[dir].dst == inner.dst.
	 *
	 * A bogus packet could look like this:
	 *   Inner: B->T
	 *   Outer: B->X (other machine reachable by T).
	 *
	 * In this case, lookup yields connection A->B and will
	 * set packet from B->X as *RELATED*, even though no connection
	 * from X was ever seen.
	 */
	ct = nf_ct_tuplehash_to_ctrack(h);
	dir = NF_CT_DIRECTION(h);
	ct_daddr = &ct->tuplehash[dir].tuple.dst.u3;
	if (!nf_inet_addr_cmp(outer_daddr, ct_daddr)) {
		if (state->pf == AF_INET) {
			nf_l4proto_log_invalid(skb, state->net, state->pf,
					       l4proto,
					       "outer daddr %pI4 != inner %pI4",
					       &outer_daddr->ip, &ct_daddr->ip);
		} else if (state->pf == AF_INET6) {
			nf_l4proto_log_invalid(skb, state->net, state->pf,
					       l4proto,
					       "outer daddr %pI6 != inner %pI6",
					       &outer_daddr->ip6, &ct_daddr->ip6);
		}
		nf_ct_put(ct);
		return -NF_ACCEPT;
	}

	ctinfo = IP_CT_RELATED;
	if (dir == IP_CT_DIR_REPLY)
		ctinfo += IP_CT_IS_REPLY;

	/* Update skb to refer to this connection */
	nf_ct_set(skb, ct, ctinfo);
	return NF_ACCEPT;
}