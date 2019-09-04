#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ all; } ;
struct TYPE_7__ {scalar_t__ all; } ;
struct nf_nat_range2 {int flags; TYPE_4__ max_proto; TYPE_3__ min_proto; } ;
struct nf_nat_l4proto {int /*<<< orphan*/  (* unique_tuple ) (struct nf_nat_l3proto const*,struct nf_conntrack_tuple const*,struct nf_nat_range2 const*,int,struct nf_conn*) ;scalar_t__ (* in_range ) (struct nf_conntrack_tuple const*,int,TYPE_3__*,TYPE_4__*) ;} ;
struct nf_nat_l3proto {int dummy; } ;
struct nf_conntrack_zone {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  protonum; } ;
struct TYPE_5__ {int /*<<< orphan*/  l3num; } ;
typedef  struct nf_conntrack_tuple {TYPE_2__ dst; TYPE_1__ src; } const nf_conntrack_tuple ;
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int NF_NAT_RANGE_PROTO_OFFSET ; 
 int NF_NAT_RANGE_PROTO_RANDOM_ALL ; 
 int NF_NAT_RANGE_PROTO_SPECIFIED ; 
 struct nf_nat_l3proto* __nf_nat_l3proto_find (int /*<<< orphan*/ ) ; 
 struct nf_nat_l4proto* __nf_nat_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_appropriate_src (struct net*,struct nf_conntrack_zone const*,struct nf_nat_l3proto const*,struct nf_nat_l4proto const*,struct nf_conntrack_tuple const*,struct nf_conntrack_tuple const*,struct nf_nat_range2 const*) ; 
 int /*<<< orphan*/  find_best_ips_proto (struct nf_conntrack_zone const*,struct nf_conntrack_tuple const*,struct nf_nat_range2 const*,struct nf_conn*,int) ; 
 scalar_t__ in_range (struct nf_nat_l3proto const*,struct nf_nat_l4proto const*,struct nf_conntrack_tuple const*,struct nf_nat_range2 const*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 struct nf_conntrack_zone* nf_ct_zone (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_nat_used_tuple (struct nf_conntrack_tuple const*,struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct nf_conntrack_tuple const*,int,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (struct nf_nat_l3proto const*,struct nf_conntrack_tuple const*,struct nf_nat_range2 const*,int,struct nf_conn*) ; 

__attribute__((used)) static void
get_unique_tuple(struct nf_conntrack_tuple *tuple,
		 const struct nf_conntrack_tuple *orig_tuple,
		 const struct nf_nat_range2 *range,
		 struct nf_conn *ct,
		 enum nf_nat_manip_type maniptype)
{
	const struct nf_conntrack_zone *zone;
	const struct nf_nat_l3proto *l3proto;
	const struct nf_nat_l4proto *l4proto;
	struct net *net = nf_ct_net(ct);

	zone = nf_ct_zone(ct);

	rcu_read_lock();
	l3proto = __nf_nat_l3proto_find(orig_tuple->src.l3num);
	l4proto = __nf_nat_l4proto_find(orig_tuple->src.l3num,
					orig_tuple->dst.protonum);

	/* 1) If this srcip/proto/src-proto-part is currently mapped,
	 * and that same mapping gives a unique tuple within the given
	 * range, use that.
	 *
	 * This is only required for source (ie. NAT/masq) mappings.
	 * So far, we don't do local source mappings, so multiple
	 * manips not an issue.
	 */
	if (maniptype == NF_NAT_MANIP_SRC &&
	    !(range->flags & NF_NAT_RANGE_PROTO_RANDOM_ALL)) {
		/* try the original tuple first */
		if (in_range(l3proto, l4proto, orig_tuple, range)) {
			if (!nf_nat_used_tuple(orig_tuple, ct)) {
				*tuple = *orig_tuple;
				goto out;
			}
		} else if (find_appropriate_src(net, zone, l3proto, l4proto,
						orig_tuple, tuple, range)) {
			pr_debug("get_unique_tuple: Found current src map\n");
			if (!nf_nat_used_tuple(tuple, ct))
				goto out;
		}
	}

	/* 2) Select the least-used IP/proto combination in the given range */
	*tuple = *orig_tuple;
	find_best_ips_proto(zone, tuple, range, ct, maniptype);

	/* 3) The per-protocol part of the manip is made to map into
	 * the range to make a unique tuple.
	 */

	/* Only bother mapping if it's not already in range and unique */
	if (!(range->flags & NF_NAT_RANGE_PROTO_RANDOM_ALL)) {
		if (range->flags & NF_NAT_RANGE_PROTO_SPECIFIED) {
			if (!(range->flags & NF_NAT_RANGE_PROTO_OFFSET) &&
			    l4proto->in_range(tuple, maniptype,
			          &range->min_proto,
			          &range->max_proto) &&
			    (range->min_proto.all == range->max_proto.all ||
			     !nf_nat_used_tuple(tuple, ct)))
				goto out;
		} else if (!nf_nat_used_tuple(tuple, ct)) {
			goto out;
		}
	}

	/* Last chance: get protocol to try to obtain unique tuple. */
	l4proto->unique_tuple(l3proto, tuple, range, maniptype, ct);
out:
	rcu_read_unlock();
}