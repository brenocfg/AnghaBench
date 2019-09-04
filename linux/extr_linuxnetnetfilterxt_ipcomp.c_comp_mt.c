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
struct xt_ipcomp {int invflags; int /*<<< orphan*/ * spis; } ;
struct xt_action_param {scalar_t__ fragoff; int hotdrop; int /*<<< orphan*/  thoff; struct xt_ipcomp* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ip_comp_hdr {int /*<<< orphan*/  cpi; } ;
typedef  int /*<<< orphan*/  _comphdr ;

/* Variables and functions */
 int XT_IPCOMP_INV_SPI ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct ip_comp_hdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct ip_comp_hdr*) ; 
 int spi_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool comp_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	struct ip_comp_hdr _comphdr;
	const struct ip_comp_hdr *chdr;
	const struct xt_ipcomp *compinfo = par->matchinfo;

	/* Must not be a fragment. */
	if (par->fragoff != 0)
		return false;

	chdr = skb_header_pointer(skb, par->thoff, sizeof(_comphdr), &_comphdr);
	if (chdr == NULL) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		pr_debug("Dropping evil IPComp tinygram.\n");
		par->hotdrop = true;
		return false;
	}

	return spi_match(compinfo->spis[0], compinfo->spis[1],
			 ntohs(chdr->cpi),
			 !!(compinfo->invflags & XT_IPCOMP_INV_SPI));
}