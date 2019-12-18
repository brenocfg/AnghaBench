#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  len; } ;
struct sk_buff {unsigned int len; } ;
struct nf_hook_state {scalar_t__ hook; int /*<<< orphan*/  pf; TYPE_2__* net; } ;
typedef  int /*<<< orphan*/  _hdr ;
struct TYPE_3__ {scalar_t__ sysctl_checksum; } ;
struct TYPE_4__ {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ NF_INET_PRE_ROUTING ; 
 scalar_t__ nf_checksum (struct sk_buff*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct udphdr*) ; 
 int /*<<< orphan*/  udp_error_log (struct sk_buff*,struct nf_hook_state const*,char*) ; 

__attribute__((used)) static bool udp_error(struct sk_buff *skb,
		      unsigned int dataoff,
		      const struct nf_hook_state *state)
{
	unsigned int udplen = skb->len - dataoff;
	const struct udphdr *hdr;
	struct udphdr _hdr;

	/* Header is too small? */
	hdr = skb_header_pointer(skb, dataoff, sizeof(_hdr), &_hdr);
	if (!hdr) {
		udp_error_log(skb, state, "short packet");
		return true;
	}

	/* Truncated/malformed packets */
	if (ntohs(hdr->len) > udplen || ntohs(hdr->len) < sizeof(*hdr)) {
		udp_error_log(skb, state, "truncated/malformed packet");
		return true;
	}

	/* Packet with no checksum */
	if (!hdr->check)
		return false;

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 * FIXME: Source route IP option packets --RR */
	if (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    nf_checksum(skb, state->hook, dataoff, IPPROTO_UDP, state->pf)) {
		udp_error_log(skb, state, "bad checksum");
		return true;
	}

	return false;
}