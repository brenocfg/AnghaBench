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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; int /*<<< orphan*/  pf; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 scalar_t__ IP_CT_DIR_REPLY ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_ESTABLISHED_REPLY ; 
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 scalar_t__ IS_ERR (struct nf_conntrack_tuple_hash*) ; 
 scalar_t__ NF_CT_DIRECTION (struct nf_conntrack_tuple_hash*) ; 
 int PTR_ERR (struct nf_conntrack_tuple_hash*) ; 
 struct nf_conntrack_tuple_hash* __nf_conntrack_find_get (int /*<<< orphan*/ ,struct nf_conntrack_zone const*,struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_conntrack_raw (struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* init_conntrack (int /*<<< orphan*/ ,struct nf_conn*,struct nf_conntrack_tuple*,struct sk_buff*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_get_tuple (struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 struct nf_conntrack_zone* nf_ct_zone_tmpl (struct nf_conn*,struct sk_buff*,struct nf_conntrack_zone*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
resolve_normal_ct(struct nf_conn *tmpl,
		  struct sk_buff *skb,
		  unsigned int dataoff,
		  u_int8_t protonum,
		  const struct nf_hook_state *state)
{
	const struct nf_conntrack_zone *zone;
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_tuple_hash *h;
	enum ip_conntrack_info ctinfo;
	struct nf_conntrack_zone tmp;
	struct nf_conn *ct;
	u32 hash;

	if (!nf_ct_get_tuple(skb, skb_network_offset(skb),
			     dataoff, state->pf, protonum, state->net,
			     &tuple)) {
		pr_debug("Can't get tuple\n");
		return 0;
	}

	/* look for tuple match */
	zone = nf_ct_zone_tmpl(tmpl, skb, &tmp);
	hash = hash_conntrack_raw(&tuple, state->net);
	h = __nf_conntrack_find_get(state->net, zone, &tuple, hash);
	if (!h) {
		h = init_conntrack(state->net, tmpl, &tuple,
				   skb, dataoff, hash);
		if (!h)
			return 0;
		if (IS_ERR(h))
			return PTR_ERR(h);
	}
	ct = nf_ct_tuplehash_to_ctrack(h);

	/* It exists; we have (non-exclusive) reference. */
	if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY) {
		ctinfo = IP_CT_ESTABLISHED_REPLY;
	} else {
		/* Once we've had two way comms, always ESTABLISHED. */
		if (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) {
			pr_debug("normal packet for %p\n", ct);
			ctinfo = IP_CT_ESTABLISHED;
		} else if (test_bit(IPS_EXPECTED_BIT, &ct->status)) {
			pr_debug("related packet for %p\n", ct);
			ctinfo = IP_CT_RELATED;
		} else {
			pr_debug("new packet for %p\n", ct);
			ctinfo = IP_CT_NEW;
		}
	}
	nf_ct_set(skb, ct, ctinfo);
	return 0;
}