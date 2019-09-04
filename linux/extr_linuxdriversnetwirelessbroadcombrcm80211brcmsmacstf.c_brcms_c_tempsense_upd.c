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
typedef  int uint ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_c_info {TYPE_1__* stf; TYPE_2__* band; } ;
struct TYPE_4__ {struct brcms_phy_pub* pi; } ;
struct TYPE_3__ {int txchain; int hw_txchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_stf_txchain_set (struct brcms_c_info*,int,int) ; 
 int wlc_phy_stf_chain_active_get (struct brcms_phy_pub*) ; 

void brcms_c_tempsense_upd(struct brcms_c_info *wlc)
{
	struct brcms_phy_pub *pi = wlc->band->pi;
	uint active_chains, txchain;

	/* Check if the chip is too hot. Disable one Tx chain, if it is */
	/* high 4 bits are for Rx chain, low 4 bits are  for Tx chain */
	active_chains = wlc_phy_stf_chain_active_get(pi);
	txchain = active_chains & 0xf;

	if (wlc->stf->txchain == wlc->stf->hw_txchain) {
		if (txchain && (txchain < wlc->stf->hw_txchain))
			/* turn off 1 tx chain */
			brcms_c_stf_txchain_set(wlc, txchain, true);
	} else if (wlc->stf->txchain < wlc->stf->hw_txchain) {
		if (txchain == wlc->stf->hw_txchain)
			/* turn back on txchain */
			brcms_c_stf_txchain_set(wlc, txchain, true);
	}
}