#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_3__ icmp; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct nf_conntrack_tuple {TYPE_5__ src; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ echo; } ;
struct icmphdr {TYPE_2__ un; int /*<<< orphan*/  checksum; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
icmp_manip_pkt(struct sk_buff *skb,
	       unsigned int iphdroff, unsigned int hdroff,
	       const struct nf_conntrack_tuple *tuple,
	       enum nf_nat_manip_type maniptype)
{
	struct icmphdr *hdr;

	if (skb_ensure_writable(skb, hdroff + sizeof(*hdr)))
		return false;

	hdr = (struct icmphdr *)(skb->data + hdroff);
	inet_proto_csum_replace2(&hdr->checksum, skb,
				 hdr->un.echo.id, tuple->src.u.icmp.id, false);
	hdr->un.echo.id = tuple->src.u.icmp.id;
	return true;
}