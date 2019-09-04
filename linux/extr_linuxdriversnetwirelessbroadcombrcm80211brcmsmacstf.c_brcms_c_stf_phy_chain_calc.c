#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct ssb_sprom {int txchain; int rxchain; } ;
struct brcms_c_info {TYPE_4__* stf; int /*<<< orphan*/  band; TYPE_3__* hw; } ;
struct TYPE_8__ {int hw_txchain; int hw_rxchain; int txchain; int rxchain; int /*<<< orphan*/  spatial_policy; int /*<<< orphan*/  txcore; void* rxstreams; void* txstreams; } ;
struct TYPE_7__ {TYPE_2__* d11core; } ;
struct TYPE_6__ {TYPE_1__* bus; } ;
struct TYPE_5__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 scalar_t__ BRCMS_ISNPHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_SPATIAL_EXPANSION ; 
 int RXCHAIN_DEF ; 
 int RXCHAIN_DEF_NPHY ; 
 int TXCHAIN_DEF ; 
 int TXCHAIN_DEF_NPHY ; 
 int /*<<< orphan*/  brcms_c_stf_spatial_policy_set (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ hweight8 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txcore_default ; 

void brcms_c_stf_phy_chain_calc(struct brcms_c_info *wlc)
{
	struct ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;

	/* get available rx/tx chains */
	wlc->stf->hw_txchain = sprom->txchain;
	wlc->stf->hw_rxchain = sprom->rxchain;

	/* these parameter are intended to be used for all PHY types */
	if (wlc->stf->hw_txchain == 0 || wlc->stf->hw_txchain == 0xf) {
		if (BRCMS_ISNPHY(wlc->band))
			wlc->stf->hw_txchain = TXCHAIN_DEF_NPHY;
		else
			wlc->stf->hw_txchain = TXCHAIN_DEF;
	}

	wlc->stf->txchain = wlc->stf->hw_txchain;
	wlc->stf->txstreams = (u8) hweight8(wlc->stf->hw_txchain);

	if (wlc->stf->hw_rxchain == 0 || wlc->stf->hw_rxchain == 0xf) {
		if (BRCMS_ISNPHY(wlc->band))
			wlc->stf->hw_rxchain = RXCHAIN_DEF_NPHY;
		else
			wlc->stf->hw_rxchain = RXCHAIN_DEF;
	}

	wlc->stf->rxchain = wlc->stf->hw_rxchain;
	wlc->stf->rxstreams = (u8) hweight8(wlc->stf->hw_rxchain);

	/* initialize the txcore table */
	memcpy(wlc->stf->txcore, txcore_default, sizeof(wlc->stf->txcore));

	/* default spatial_policy */
	wlc->stf->spatial_policy = MIN_SPATIAL_EXPANSION;
	brcms_c_stf_spatial_policy_set(wlc, MIN_SPATIAL_EXPANSION);
}