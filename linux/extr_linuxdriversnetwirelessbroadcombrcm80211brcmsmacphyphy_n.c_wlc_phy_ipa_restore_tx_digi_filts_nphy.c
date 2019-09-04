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
struct brcms_phy {scalar_t__ bw; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** NPHY_IPA_REV4_txdigi_filtcoeffs ; 
 int NPHY_NUM_DIG_FILT_COEFFS ; 
 scalar_t__ WL_CHANSPEC_BW_40 ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_ipa_restore_tx_digi_filts_nphy(struct brcms_phy *pi)
{
	int j;

	if (pi->bw == WL_CHANSPEC_BW_40) {
		for (j = 0; j < NPHY_NUM_DIG_FILT_COEFFS; j++)
			write_phy_reg(pi, 0x195 + j,
				      NPHY_IPA_REV4_txdigi_filtcoeffs[4][j]);
	} else {
		for (j = 0; j < NPHY_NUM_DIG_FILT_COEFFS; j++)
			write_phy_reg(pi, 0x186 + j,
				      NPHY_IPA_REV4_txdigi_filtcoeffs[3][j]);
	}
}