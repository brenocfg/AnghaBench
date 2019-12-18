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
struct nft_set_ext {int dummy; } ;
struct TYPE_5__ {void* code; } ;
struct nft_regs {TYPE_2__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct TYPE_6__ {unsigned int count; } ;
struct nft_connlimit {unsigned int limit; int invert; TYPE_3__ list; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {TYPE_1__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 void* NFT_BREAK ; 
 void* NF_DROP ; 
 scalar_t__ nf_conncount_add (int /*<<< orphan*/ ,TYPE_3__*,struct nf_conntrack_tuple const*,struct nf_conntrack_zone const*) ; 
 struct nf_conn* nf_ct_get (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 struct nf_conntrack_zone* nf_ct_zone (struct nf_conn const*) ; 
 struct nf_conntrack_zone nf_ct_zone_dflt ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_pf (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  skb_network_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nft_connlimit_do_eval(struct nft_connlimit *priv,
					 struct nft_regs *regs,
					 const struct nft_pktinfo *pkt,
					 const struct nft_set_ext *ext)
{
	const struct nf_conntrack_zone *zone = &nf_ct_zone_dflt;
	const struct nf_conntrack_tuple *tuple_ptr;
	struct nf_conntrack_tuple tuple;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;
	unsigned int count;

	tuple_ptr = &tuple;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (ct != NULL) {
		tuple_ptr = &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
		zone = nf_ct_zone(ct);
	} else if (!nf_ct_get_tuplepr(pkt->skb, skb_network_offset(pkt->skb),
				      nft_pf(pkt), nft_net(pkt), &tuple)) {
		regs->verdict.code = NF_DROP;
		return;
	}

	if (nf_conncount_add(nft_net(pkt), &priv->list, tuple_ptr, zone)) {
		regs->verdict.code = NF_DROP;
		return;
	}

	count = priv->list.count;

	if ((count > priv->limit) ^ priv->invert) {
		regs->verdict.code = NFT_BREAK;
		return;
	}
}