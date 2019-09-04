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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  ct_general; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_expect* __nf_ct_expect_find (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple*) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_conntrack_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_delete (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct nf_conntrack_tuple*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff const*) ; 

__attribute__((used)) static struct nf_conntrack_expect *
ovs_ct_expect_find(struct net *net, const struct nf_conntrack_zone *zone,
		   u16 proto, const struct sk_buff *skb)
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_expect *exp;

	if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb), proto, net, &tuple))
		return NULL;

	exp = __nf_ct_expect_find(net, zone, &tuple);
	if (exp) {
		struct nf_conntrack_tuple_hash *h;

		/* Delete existing conntrack entry, if it clashes with the
		 * expectation.  This can happen since conntrack ALGs do not
		 * check for clashes between (new) expectations and existing
		 * conntrack entries.  nf_conntrack_in() will check the
		 * expectations only if a conntrack entry can not be found,
		 * which can lead to OVS finding the expectation (here) in the
		 * init direction, but which will not be removed by the
		 * nf_conntrack_in() call, if a matching conntrack entry is
		 * found instead.  In this case all init direction packets
		 * would be reported as new related packets, while reply
		 * direction packets would be reported as un-related
		 * established packets.
		 */
		h = nf_conntrack_find_get(net, zone, &tuple);
		if (h) {
			struct nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

			nf_ct_delete(ct, 0, 0);
			nf_conntrack_put(&ct->ct_general);
		}
	}

	return exp;
}