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
typedef  void* u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ssb_sprom {int ofdm2gpo; int* mcs2gpo; int cddpo; int stbcpo; int ofdm5glpo; int* mcs5glpo; int ofdm5gpo; int* mcs5gpo; int ofdm5ghpo; int* mcs5ghpo; int cck2gpo; TYPE_2__* core_pwr_info; } ;
struct b43_phy {scalar_t__ type; int rev; } ;
struct b43_wldev {struct b43_phy phy; TYPE_1__* dev; } ;
struct b43_ppr_rates {void** mcs_20_cdd; void** ofdm_20_cdd; void** mcs_20_stbc; void** mcs_20_sdm; void** ofdm; void** mcs_20; void** cck; } ;
struct b43_ppr {struct b43_ppr_rates rates; } ;
typedef  enum b43_band { ____Placeholder_b43_band } b43_band ;
struct TYPE_4__ {int /*<<< orphan*/  maxpwr_5gh; int /*<<< orphan*/  maxpwr_5g; int /*<<< orphan*/  maxpwr_5gl; int /*<<< orphan*/  maxpwr_2g; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
#define  B43_BAND_2G 131 
#define  B43_BAND_5G_HI 130 
#define  B43_BAND_5G_LO 129 
#define  B43_BAND_5G_MI 128 
 scalar_t__ B43_PHYTYPE_N ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool b43_ppr_load_max_from_sprom(struct b43_wldev *dev, struct b43_ppr *ppr,
				 enum b43_band band)
{
	struct b43_ppr_rates *rates = &ppr->rates;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy *phy = &dev->phy;
	u8 maxpwr, off;
	u32 sprom_ofdm_po;
	u16 *sprom_mcs_po;
	u8 extra_cdd_po, extra_stbc_po;
	int i;

	switch (band) {
	case B43_BAND_2G:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_2g,
			     sprom->core_pwr_info[1].maxpwr_2g);
		sprom_ofdm_po = sprom->ofdm2gpo;
		sprom_mcs_po = sprom->mcs2gpo;
		extra_cdd_po = (sprom->cddpo >> 0) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 0) & 0xf;
		break;
	case B43_BAND_5G_LO:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5gl,
			     sprom->core_pwr_info[1].maxpwr_5gl);
		sprom_ofdm_po = sprom->ofdm5glpo;
		sprom_mcs_po = sprom->mcs5glpo;
		extra_cdd_po = (sprom->cddpo >> 8) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 8) & 0xf;
		break;
	case B43_BAND_5G_MI:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5g,
			     sprom->core_pwr_info[1].maxpwr_5g);
		sprom_ofdm_po = sprom->ofdm5gpo;
		sprom_mcs_po = sprom->mcs5gpo;
		extra_cdd_po = (sprom->cddpo >> 4) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 4) & 0xf;
		break;
	case B43_BAND_5G_HI:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5gh,
			     sprom->core_pwr_info[1].maxpwr_5gh);
		sprom_ofdm_po = sprom->ofdm5ghpo;
		sprom_mcs_po = sprom->mcs5ghpo;
		extra_cdd_po = (sprom->cddpo >> 12) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 12) & 0xf;
		break;
	default:
		WARN_ON_ONCE(1);
		return false;
	}

	if (band == B43_BAND_2G) {
		for (i = 0; i < 4; i++) {
			off = ((sprom->cck2gpo >> (i * 4)) & 0xf) * 2;
			rates->cck[i] = maxpwr - off;
		}
	}

	/* OFDM */
	for (i = 0; i < 8; i++) {
		off = ((sprom_ofdm_po >> (i * 4)) & 0xf) * 2;
		rates->ofdm[i] = maxpwr - off;
	}

	/* MCS 20 SISO */
	rates->mcs_20[0] = rates->ofdm[0];
	rates->mcs_20[1] = rates->ofdm[2];
	rates->mcs_20[2] = rates->ofdm[3];
	rates->mcs_20[3] = rates->ofdm[4];
	rates->mcs_20[4] = rates->ofdm[5];
	rates->mcs_20[5] = rates->ofdm[6];
	rates->mcs_20[6] = rates->ofdm[7];
	rates->mcs_20[7] = rates->ofdm[7];

	/* MCS 20 CDD */
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_cdd[i] = maxpwr - off;
		if (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_cdd[i] -= extra_cdd_po;
	}
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_cdd[4 + i] = maxpwr - off;
		if (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_cdd[4 + i] -= extra_cdd_po;
	}

	/* OFDM 20 CDD */
	rates->ofdm_20_cdd[0] = rates->mcs_20_cdd[0];
	rates->ofdm_20_cdd[1] = rates->mcs_20_cdd[0];
	rates->ofdm_20_cdd[2] = rates->mcs_20_cdd[1];
	rates->ofdm_20_cdd[3] = rates->mcs_20_cdd[2];
	rates->ofdm_20_cdd[4] = rates->mcs_20_cdd[3];
	rates->ofdm_20_cdd[5] = rates->mcs_20_cdd[4];
	rates->ofdm_20_cdd[6] = rates->mcs_20_cdd[5];
	rates->ofdm_20_cdd[7] = rates->mcs_20_cdd[6];

	/* MCS 20 STBC */
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_stbc[i] = maxpwr - off;
		if (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_stbc[i] -= extra_stbc_po;
	}
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_stbc[4 + i] = maxpwr - off;
		if (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_stbc[4 + i] -= extra_stbc_po;
	}

	/* MCS 20 SDM */
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[2] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_sdm[i] = maxpwr - off;
	}
	for (i = 0; i < 4; i++) {
		off = ((sprom_mcs_po[3] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_sdm[4 + i] = maxpwr - off;
	}

	return true;
}