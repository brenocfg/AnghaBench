#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct udphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  len; } ;
struct sk_buff {unsigned int len; } ;
struct nf_conn {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl_checksum; } ;
struct net {TYPE_1__ ct; } ;
typedef  int /*<<< orphan*/  _hdr ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int NF_ACCEPT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 scalar_t__ nf_checksum (struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct udphdr*) ; 
 int /*<<< orphan*/  udp_error_log (struct sk_buff*,struct net*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int udp_error(struct net *net, struct nf_conn *tmpl, struct sk_buff *skb,
		     unsigned int dataoff,
		     u_int8_t pf,
		     unsigned int hooknum)
{
	unsigned int udplen = skb->len - dataoff;
	const struct udphdr *hdr;
	struct udphdr _hdr;

	/* Header is too small? */
	hdr = skb_header_pointer(skb, dataoff, sizeof(_hdr), &_hdr);
	if (hdr == NULL) {
		udp_error_log(skb, net, pf, "short packet");
		return -NF_ACCEPT;
	}

	/* Truncated/malformed packets */
	if (ntohs(hdr->len) > udplen || ntohs(hdr->len) < sizeof(*hdr)) {
		udp_error_log(skb, net, pf, "truncated/malformed packet");
		return -NF_ACCEPT;
	}

	/* Packet with no checksum */
	if (!hdr->check)
		return NF_ACCEPT;

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 * FIXME: Source route IP option packets --RR */
	if (net->ct.sysctl_checksum && hooknum == NF_INET_PRE_ROUTING &&
	    nf_checksum(skb, hooknum, dataoff, IPPROTO_UDP, pf)) {
		udp_error_log(skb, net, pf, "bad checksum");
		return -NF_ACCEPT;
	}

	return NF_ACCEPT;
}