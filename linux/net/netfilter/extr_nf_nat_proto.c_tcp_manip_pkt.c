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
struct tcphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ tcp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ tcp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_csum_update (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,struct nf_conntrack_tuple const*,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
tcp_manip_pkt(struct sk_buff *skb,
	      unsigned int iphdroff, unsigned int hdroff,
	      const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype)
{
	struct tcphdr *hdr;
	__be16 *portptr, newport, oldport;
	int hdrsize = 8; /* TCP connection tracking guarantees this much */

	/* this could be a inner header returned in icmp packet; in such
	   cases we cannot update the checksum field since it is outside of
	   the 8 bytes of transport layer headers we are guaranteed */
	if (skb->len >= hdroff + sizeof(struct tcphdr))
		hdrsize = sizeof(struct tcphdr);

	if (skb_ensure_writable(skb, hdroff + hdrsize))
		return false;

	hdr = (struct tcphdr *)(skb->data + hdroff);

	if (maniptype == NF_NAT_MANIP_SRC) {
		/* Get rid of src port */
		newport = tuple->src.u.tcp.port;
		portptr = &hdr->source;
	} else {
		/* Get rid of dst port */
		newport = tuple->dst.u.tcp.port;
		portptr = &hdr->dest;
	}

	oldport = *portptr;
	*portptr = newport;

	if (hdrsize < sizeof(*hdr))
		return true;

	nf_csum_update(skb, iphdroff, &hdr->check, tuple, maniptype);
	inet_proto_csum_replace2(&hdr->check, skb, oldport, newport, false);
	return true;
}