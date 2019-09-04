#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_6__ icmp; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ icmp; } ;
struct nf_nat_range2 {int flags; TYPE_7__ min_proto; TYPE_2__ max_proto; } ;
struct nf_nat_l3proto {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_3__ icmp; } ;
struct TYPE_12__ {TYPE_4__ u; } ;
struct nf_conntrack_tuple {TYPE_5__ src; } ;
struct nf_conn {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int NF_NAT_RANGE_PROTO_SPECIFIED ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  nf_nat_used_tuple (struct nf_conntrack_tuple*,struct nf_conn const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
icmpv6_unique_tuple(const struct nf_nat_l3proto *l3proto,
		    struct nf_conntrack_tuple *tuple,
		    const struct nf_nat_range2 *range,
		    enum nf_nat_manip_type maniptype,
		    const struct nf_conn *ct)
{
	static u16 id;
	unsigned int range_size;
	unsigned int i;

	range_size = ntohs(range->max_proto.icmp.id) -
		     ntohs(range->min_proto.icmp.id) + 1;

	if (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED))
		range_size = 0xffff;

	for (i = 0; ; ++id) {
		tuple->src.u.icmp.id = htons(ntohs(range->min_proto.icmp.id) +
					     (id % range_size));
		if (++i == range_size || !nf_nat_used_tuple(tuple, ct))
			return;
	}
}