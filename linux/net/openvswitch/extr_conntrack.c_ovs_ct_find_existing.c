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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_zone {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {TYPE_1__ dst; } ;
struct nf_conntrack_tuple_hash {TYPE_2__ tuple; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {struct nf_conntrack_tuple_hash* tuplehash; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_zone const*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  ovs_ct_get_info (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static struct nf_conn *
ovs_ct_find_existing(struct net *net, const struct nf_conntrack_zone *zone,
		     u8 l3num, struct sk_buff *skb, bool natted)
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_tuple_hash *h;
	struct nf_conn *ct;

	if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb), l3num,
			       net, &tuple)) {
		pr_debug("ovs_ct_find_existing: Can't get tuple\n");
		return NULL;
	}

	/* Must invert the tuple if skb has been transformed by NAT. */
	if (natted) {
		struct nf_conntrack_tuple inverse;

		if (!nf_ct_invert_tuple(&inverse, &tuple)) {
			pr_debug("ovs_ct_find_existing: Inversion failed!\n");
			return NULL;
		}
		tuple = inverse;
	}

	/* look for tuple match */
	h = nf_conntrack_find_get(net, zone, &tuple);
	if (!h)
		return NULL;   /* Not found. */

	ct = nf_ct_tuplehash_to_ctrack(h);

	/* Inverted packet tuple matches the reverse direction conntrack tuple,
	 * select the other tuplehash to get the right 'ctinfo' bits for this
	 * packet.
	 */
	if (natted)
		h = &ct->tuplehash[!h->tuple.dst.dir];

	nf_ct_set(skb, ct, ovs_ct_get_info(h));
	return ct;
}