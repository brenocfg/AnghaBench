#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nf_nat_hook {scalar_t__ (* manip_pkt ) (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ,size_t) ;} ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct TYPE_28__ {int /*<<< orphan*/  all; } ;
struct TYPE_26__ {int /*<<< orphan*/  all; } ;
struct TYPE_15__ {TYPE_9__ u; TYPE_7__ u3; } ;
struct TYPE_22__ {int /*<<< orphan*/  all; } ;
struct TYPE_20__ {int /*<<< orphan*/  all; } ;
struct TYPE_23__ {TYPE_3__ u; TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_10__ dst; TYPE_4__ src; } ;
struct nf_conn {int status; TYPE_14__* tuplehash; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_27__ {int /*<<< orphan*/  all; } ;
struct TYPE_24__ {int /*<<< orphan*/  all; } ;
struct TYPE_21__ {int /*<<< orphan*/  all; } ;
struct TYPE_25__ {TYPE_5__ u; TYPE_2__ u3; } ;
struct TYPE_16__ {int /*<<< orphan*/  all; } ;
struct TYPE_17__ {TYPE_11__ u; TYPE_8__ u3; } ;
struct TYPE_18__ {TYPE_12__ dst; TYPE_6__ src; } ;
struct TYPE_19__ {TYPE_13__ tuple; } ;

/* Variables and functions */
 int IPS_DST_NAT ; 
 int IPS_SRC_NAT ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 scalar_t__ NF_DROP ; 
 int /*<<< orphan*/  NF_NAT_MANIP_DST ; 
 int /*<<< orphan*/  NF_NAT_MANIP_SRC ; 
 int get_l4proto (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuple (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct nf_conntrack_tuple*) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  nf_ct_zone (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_nat_hook ; 
 struct nf_nat_hook* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 scalar_t__ stub1 (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub2 (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int nf_conntrack_update(struct net *net, struct sk_buff *skb)
{
	struct nf_conntrack_tuple_hash *h;
	struct nf_conntrack_tuple tuple;
	enum ip_conntrack_info ctinfo;
	struct nf_nat_hook *nat_hook;
	unsigned int status;
	struct nf_conn *ct;
	int dataoff;
	u16 l3num;
	u8 l4num;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || nf_ct_is_confirmed(ct))
		return 0;

	l3num = nf_ct_l3num(ct);

	dataoff = get_l4proto(skb, skb_network_offset(skb), l3num, &l4num);
	if (dataoff <= 0)
		return -1;

	if (!nf_ct_get_tuple(skb, skb_network_offset(skb), dataoff, l3num,
			     l4num, net, &tuple))
		return -1;

	if (ct->status & IPS_SRC_NAT) {
		memcpy(tuple.src.u3.all,
		       ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.all,
		       sizeof(tuple.src.u3.all));
		tuple.src.u.all =
			ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.all;
	}

	if (ct->status & IPS_DST_NAT) {
		memcpy(tuple.dst.u3.all,
		       ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.all,
		       sizeof(tuple.dst.u3.all));
		tuple.dst.u.all =
			ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.all;
	}

	h = nf_conntrack_find_get(net, nf_ct_zone(ct), &tuple);
	if (!h)
		return 0;

	/* Store status bits of the conntrack that is clashing to re-do NAT
	 * mangling according to what it has been done already to this packet.
	 */
	status = ct->status;

	nf_ct_put(ct);
	ct = nf_ct_tuplehash_to_ctrack(h);
	nf_ct_set(skb, ct, ctinfo);

	nat_hook = rcu_dereference(nf_nat_hook);
	if (!nat_hook)
		return 0;

	if (status & IPS_SRC_NAT &&
	    nat_hook->manip_pkt(skb, ct, NF_NAT_MANIP_SRC,
				IP_CT_DIR_ORIGINAL) == NF_DROP)
		return -1;

	if (status & IPS_DST_NAT &&
	    nat_hook->manip_pkt(skb, ct, NF_NAT_MANIP_DST,
				IP_CT_DIR_ORIGINAL) == NF_DROP)
		return -1;

	return 0;
}