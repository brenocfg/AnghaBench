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
struct sk_buff {unsigned int len; scalar_t__ ip_summed; scalar_t__ data; } ;
struct sctphdr {int /*<<< orphan*/  checksum; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ sctp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ sctp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  sctp_compute_cksum (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
sctp_manip_pkt(struct sk_buff *skb,
	       unsigned int iphdroff, unsigned int hdroff,
	       const struct nf_conntrack_tuple *tuple,
	       enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PROTO_SCTP
	struct sctphdr *hdr;
	int hdrsize = 8;

	/* This could be an inner header returned in imcp packet; in such
	 * cases we cannot update the checksum field since it is outside
	 * of the 8 bytes of transport layer headers we are guaranteed.
	 */
	if (skb->len >= hdroff + sizeof(*hdr))
		hdrsize = sizeof(*hdr);

	if (skb_ensure_writable(skb, hdroff + hdrsize))
		return false;

	hdr = (struct sctphdr *)(skb->data + hdroff);

	if (maniptype == NF_NAT_MANIP_SRC) {
		/* Get rid of src port */
		hdr->source = tuple->src.u.sctp.port;
	} else {
		/* Get rid of dst port */
		hdr->dest = tuple->dst.u.sctp.port;
	}

	if (hdrsize < sizeof(*hdr))
		return true;

	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		hdr->checksum = sctp_compute_cksum(skb, hdroff);
		skb->ip_summed = CHECKSUM_NONE;
	}

#endif
	return true;
}