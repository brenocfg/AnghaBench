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
typedef  unsigned int u_int16_t ;
typedef  unsigned int u16 ;
struct TYPE_14__ {int /*<<< orphan*/  all; } ;
struct TYPE_9__ {int /*<<< orphan*/  all; } ;
struct TYPE_8__ {int /*<<< orphan*/  all; } ;
struct nf_nat_range2 {int flags; TYPE_7__ base_proto; TYPE_2__ max_proto; TYPE_1__ min_proto; } ;
struct nf_nat_l3proto {unsigned int (* secure_port ) (struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  all; } ;
struct TYPE_13__ {TYPE_5__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  all; } ;
struct TYPE_11__ {TYPE_3__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ src; TYPE_4__ dst; } ;
struct nf_conn {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int NF_NAT_MANIP_DST ; 
 int NF_NAT_MANIP_SRC ; 
 int NF_NAT_RANGE_PROTO_OFFSET ; 
 int NF_NAT_RANGE_PROTO_RANDOM ; 
 int NF_NAT_RANGE_PROTO_RANDOM_ALL ; 
 int NF_NAT_RANGE_PROTO_RANDOM_FULLY ; 
 int NF_NAT_RANGE_PROTO_SPECIFIED ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 scalar_t__ nf_nat_used_tuple (struct nf_conntrack_tuple*,struct nf_conn const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 unsigned int prandom_u32 () ; 
 unsigned int stub1 (struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void nf_nat_l4proto_unique_tuple(const struct nf_nat_l3proto *l3proto,
				 struct nf_conntrack_tuple *tuple,
				 const struct nf_nat_range2 *range,
				 enum nf_nat_manip_type maniptype,
				 const struct nf_conn *ct,
				 u16 *rover)
{
	unsigned int range_size, min, max, i;
	__be16 *portptr;
	u_int16_t off;

	if (maniptype == NF_NAT_MANIP_SRC)
		portptr = &tuple->src.u.all;
	else
		portptr = &tuple->dst.u.all;

	/* If no range specified... */
	if (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED)) {
		/* If it's dst rewrite, can't change port */
		if (maniptype == NF_NAT_MANIP_DST)
			return;

		if (ntohs(*portptr) < 1024) {
			/* Loose convention: >> 512 is credential passing */
			if (ntohs(*portptr) < 512) {
				min = 1;
				range_size = 511 - min + 1;
			} else {
				min = 600;
				range_size = 1023 - min + 1;
			}
		} else {
			min = 1024;
			range_size = 65535 - 1024 + 1;
		}
	} else {
		min = ntohs(range->min_proto.all);
		max = ntohs(range->max_proto.all);
		if (unlikely(max < min))
			swap(max, min);
		range_size = max - min + 1;
	}

	if (range->flags & NF_NAT_RANGE_PROTO_RANDOM) {
		off = l3proto->secure_port(tuple, maniptype == NF_NAT_MANIP_SRC
						  ? tuple->dst.u.all
						  : tuple->src.u.all);
	} else if (range->flags & NF_NAT_RANGE_PROTO_RANDOM_FULLY) {
		off = prandom_u32();
	} else if (range->flags & NF_NAT_RANGE_PROTO_OFFSET) {
		off = (ntohs(*portptr) - ntohs(range->base_proto.all));
	} else {
		off = *rover;
	}

	for (i = 0; ; ++off) {
		*portptr = htons(min + off % range_size);
		if (++i != range_size && nf_nat_used_tuple(tuple, ct))
			continue;
		if (!(range->flags & (NF_NAT_RANGE_PROTO_RANDOM_ALL|
					NF_NAT_RANGE_PROTO_OFFSET)))
			*rover = off;
		return;
	}
}