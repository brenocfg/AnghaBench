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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {TYPE_1__ dst; } ;
struct nf_conntrack_tuple_hash {TYPE_2__ tuple; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*,int) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nf_conntrack_tuple*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conntrack_tuple* nf_ct_tuple (struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  nf_ct_zone_dflt ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff const*) ; 

__attribute__((used)) static bool nf_conntrack_get_tuple_skb(struct nf_conntrack_tuple *dst_tuple,
				       const struct sk_buff *skb)
{
	const struct nf_conntrack_tuple *src_tuple;
	const struct nf_conntrack_tuple_hash *hash;
	struct nf_conntrack_tuple srctuple;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		src_tuple = nf_ct_tuple(ct, CTINFO2DIR(ctinfo));
		memcpy(dst_tuple, src_tuple, sizeof(*dst_tuple));
		return true;
	}

	if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
			       NFPROTO_IPV4, dev_net(skb->dev),
			       &srctuple))
		return false;

	hash = nf_conntrack_find_get(dev_net(skb->dev),
				     &nf_ct_zone_dflt,
				     &srctuple);
	if (!hash)
		return false;

	ct = nf_ct_tuplehash_to_ctrack(hash);
	src_tuple = nf_ct_tuple(ct, !hash->tuple.dst.dir);
	memcpy(dst_tuple, src_tuple, sizeof(*dst_tuple));
	nf_ct_put(ct);

	return true;
}