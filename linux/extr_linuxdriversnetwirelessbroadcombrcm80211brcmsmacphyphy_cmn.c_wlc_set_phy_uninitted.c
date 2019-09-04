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
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int initialized; int tx_vos; int nrssi_table_delta; int rc_cal; int mintxbias; int txpwridx; int* nphy_papd_epsilon_offset; int* nphy_txpwr_idx; int radiopwr; int** stats_11b_txpower; void* phy_spuravoid; scalar_t__ phy_pabias; TYPE_2__* nphy_txpwrindex; scalar_t__ nphy_papd_skip; TYPE_1__ pubpi; } ;
struct TYPE_4__ {int index_internal; } ;

/* Variables and functions */
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 void* SPURAVOID_AUTO ; 
 void* SPURAVOID_DISABLE ; 
 int STATIC_NUM_BB ; 
 int STATIC_NUM_RF ; 

__attribute__((used)) static void wlc_set_phy_uninitted(struct brcms_phy *pi)
{
	int i, j;

	pi->initialized = false;

	pi->tx_vos = 0xffff;
	pi->nrssi_table_delta = 0x7fffffff;
	pi->rc_cal = 0xffff;
	pi->mintxbias = 0xffff;
	pi->txpwridx = -1;
	if (ISNPHY(pi)) {
		pi->phy_spuravoid = SPURAVOID_DISABLE;

		if (NREV_GE(pi->pubpi.phy_rev, 3)
		    && NREV_LT(pi->pubpi.phy_rev, 7))
			pi->phy_spuravoid = SPURAVOID_AUTO;

		pi->nphy_papd_skip = 0;
		pi->nphy_papd_epsilon_offset[0] = 0xf588;
		pi->nphy_papd_epsilon_offset[1] = 0xf588;
		pi->nphy_txpwr_idx[0] = 128;
		pi->nphy_txpwr_idx[1] = 128;
		pi->nphy_txpwrindex[0].index_internal = 40;
		pi->nphy_txpwrindex[1].index_internal = 40;
		pi->phy_pabias = 0;
	} else {
		pi->phy_spuravoid = SPURAVOID_AUTO;
	}
	pi->radiopwr = 0xffff;
	for (i = 0; i < STATIC_NUM_RF; i++) {
		for (j = 0; j < STATIC_NUM_BB; j++)
			pi->stats_11b_txpower[i][j] = -1;
	}
}