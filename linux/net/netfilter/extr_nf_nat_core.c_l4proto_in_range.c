#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
union nf_conntrack_man_proto {int /*<<< orphan*/  all; TYPE_2__ icmp; } ;
struct TYPE_11__ {int /*<<< orphan*/  all; } ;
struct TYPE_12__ {int protonum; TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  all; TYPE_1__ icmp; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_4__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  IPPROTO_DCCP 135 
#define  IPPROTO_GRE 134 
#define  IPPROTO_ICMP 133 
#define  IPPROTO_ICMPV6 132 
#define  IPPROTO_SCTP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool l4proto_in_range(const struct nf_conntrack_tuple *tuple,
			     enum nf_nat_manip_type maniptype,
			     const union nf_conntrack_man_proto *min,
			     const union nf_conntrack_man_proto *max)
{
	__be16 port;

	switch (tuple->dst.protonum) {
	case IPPROTO_ICMP:
	case IPPROTO_ICMPV6:
		return ntohs(tuple->src.u.icmp.id) >= ntohs(min->icmp.id) &&
		       ntohs(tuple->src.u.icmp.id) <= ntohs(max->icmp.id);
	case IPPROTO_GRE: /* all fall though */
	case IPPROTO_TCP:
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE:
	case IPPROTO_DCCP:
	case IPPROTO_SCTP:
		if (maniptype == NF_NAT_MANIP_SRC)
			port = tuple->src.u.all;
		else
			port = tuple->dst.u.all;

		return ntohs(port) >= ntohs(min->all) &&
		       ntohs(port) <= ntohs(max->all);
	default:
		return true;
	}
}