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
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ dccp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ dccp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_csum_update (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,struct nf_conntrack_tuple const*,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
dccp_manip_pkt(struct sk_buff *skb,
	       unsigned int iphdroff, unsigned int hdroff,
	       const struct nf_conntrack_tuple *tuple,
	       enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PROTO_DCCP
	struct dccp_hdr *hdr;
	__be16 *portptr, oldport, newport;
	int hdrsize = 8; /* DCCP connection tracking guarantees this much */

	if (skb->len >= hdroff + sizeof(struct dccp_hdr))
		hdrsize = sizeof(struct dccp_hdr);

	if (skb_ensure_writable(skb, hdroff + hdrsize))
		return false;

	hdr = (struct dccp_hdr *)(skb->data + hdroff);

	if (maniptype == NF_NAT_MANIP_SRC) {
		newport = tuple->src.u.dccp.port;
		portptr = &hdr->dccph_sport;
	} else {
		newport = tuple->dst.u.dccp.port;
		portptr = &hdr->dccph_dport;
	}

	oldport = *portptr;
	*portptr = newport;

	if (hdrsize < sizeof(*hdr))
		return true;

	nf_csum_update(skb, iphdroff, &hdr->dccph_checksum, tuple, maniptype);
	inet_proto_csum_replace2(&hdr->dccph_checksum, skb, oldport, newport,
				 false);
#endif
	return true;
}