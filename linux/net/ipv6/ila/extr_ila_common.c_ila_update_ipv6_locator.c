#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct ila_params {int csum_mode; int /*<<< orphan*/  locator; } ;
struct ila_addr {int /*<<< orphan*/  loc; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
#define  ILA_CSUM_ADJUST_TRANSPORT 131 
#define  ILA_CSUM_NEUTRAL_MAP 130 
#define  ILA_CSUM_NEUTRAL_MAP_AUTO 129 
#define  ILA_CSUM_NO_ACTION 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct ila_addr* ila_a2i (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ila_csum_adjust_transport (struct sk_buff*,struct ila_params*) ; 
 int /*<<< orphan*/  ila_csum_do_neutral_fmt (struct ila_addr*,struct ila_params*) ; 
 int /*<<< orphan*/  ila_csum_do_neutral_nofmt (struct ila_addr*,struct ila_params*) ; 
 int /*<<< orphan*/  ila_csum_neutral_set (int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 

void ila_update_ipv6_locator(struct sk_buff *skb, struct ila_params *p,
			     bool sir2ila)
{
	struct ipv6hdr *ip6h = ipv6_hdr(skb);
	struct ila_addr *iaddr = ila_a2i(&ip6h->daddr);

	switch (p->csum_mode) {
	case ILA_CSUM_ADJUST_TRANSPORT:
		ila_csum_adjust_transport(skb, p);
		break;
	case ILA_CSUM_NEUTRAL_MAP:
		if (sir2ila) {
			if (WARN_ON(ila_csum_neutral_set(iaddr->ident))) {
				/* Checksum flag should never be
				 * set in a formatted SIR address.
				 */
				break;
			}
		} else if (!ila_csum_neutral_set(iaddr->ident)) {
			/* ILA to SIR translation and C-bit isn't
			 * set so we're good.
			 */
			break;
		}
		ila_csum_do_neutral_fmt(iaddr, p);
		break;
	case ILA_CSUM_NEUTRAL_MAP_AUTO:
		ila_csum_do_neutral_nofmt(iaddr, p);
		break;
	case ILA_CSUM_NO_ACTION:
		break;
	}

	/* Now change destination address */
	iaddr->loc = p->locator;
}