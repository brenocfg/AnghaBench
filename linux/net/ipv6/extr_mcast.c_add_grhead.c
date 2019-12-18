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
struct mld2_report {int /*<<< orphan*/  mld2r_ngrec; } ;
struct mld2_grec {int grec_type; int /*<<< orphan*/  grec_mca; scalar_t__ grec_nsrcs; scalar_t__ grec_auxwords; } ;
struct ifmcaddr6 {int /*<<< orphan*/  mca_addr; int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (scalar_t__) ; 
 struct sk_buff* mld_newpack (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct mld2_grec* skb_put (struct sk_buff*,int) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *add_grhead(struct sk_buff *skb, struct ifmcaddr6 *pmc,
	int type, struct mld2_grec **ppgr, unsigned int mtu)
{
	struct mld2_report *pmr;
	struct mld2_grec *pgr;

	if (!skb) {
		skb = mld_newpack(pmc->idev, mtu);
		if (!skb)
			return NULL;
	}
	pgr = skb_put(skb, sizeof(struct mld2_grec));
	pgr->grec_type = type;
	pgr->grec_auxwords = 0;
	pgr->grec_nsrcs = 0;
	pgr->grec_mca = pmc->mca_addr;	/* structure copy */
	pmr = (struct mld2_report *)skb_transport_header(skb);
	pmr->mld2r_ngrec = htons(ntohs(pmr->mld2r_ngrec)+1);
	*ppgr = pgr;
	return skb;
}