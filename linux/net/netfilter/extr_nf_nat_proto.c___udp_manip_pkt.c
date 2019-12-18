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
struct udphdr {scalar_t__ check; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ udp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ udp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ CSUM_MANGLED_0 ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (scalar_t__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_csum_update (struct sk_buff*,unsigned int,scalar_t__*,struct nf_conntrack_tuple const*,int) ; 

__attribute__((used)) static void
__udp_manip_pkt(struct sk_buff *skb,
	        unsigned int iphdroff, struct udphdr *hdr,
	        const struct nf_conntrack_tuple *tuple,
	        enum nf_nat_manip_type maniptype, bool do_csum)
{
	__be16 *portptr, newport;

	if (maniptype == NF_NAT_MANIP_SRC) {
		/* Get rid of src port */
		newport = tuple->src.u.udp.port;
		portptr = &hdr->source;
	} else {
		/* Get rid of dst port */
		newport = tuple->dst.u.udp.port;
		portptr = &hdr->dest;
	}
	if (do_csum) {
		nf_csum_update(skb, iphdroff, &hdr->check, tuple, maniptype);
		inet_proto_csum_replace2(&hdr->check, skb, *portptr, newport,
					 false);
		if (!hdr->check)
			hdr->check = CSUM_MANGLED_0;
	}
	*portptr = newport;
}