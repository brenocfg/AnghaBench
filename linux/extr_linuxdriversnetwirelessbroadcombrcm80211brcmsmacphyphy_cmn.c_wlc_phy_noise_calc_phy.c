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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {size_t nphy_noise_index; scalar_t__** nphy_noise_win; TYPE_1__ pubpi; } ;
typedef  scalar_t__ s8 ;
typedef  int /*<<< orphan*/  cmplx_pwr_dbm ;

/* Variables and functions */
 size_t MODINC_POW2 (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int PHY_CORE_MAX ; 
 scalar_t__ PHY_NOISE_OFFSETFACT_4322 ; 
 int /*<<< orphan*/  PHY_NOISE_WINDOW_SZ ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_compute_dB (int /*<<< orphan*/ *,scalar_t__*,size_t) ; 

__attribute__((used)) static bool
wlc_phy_noise_calc_phy(struct brcms_phy *pi, u32 *cmplx_pwr, s8 *pwr_ant)
{
	s8 cmplx_pwr_dbm[PHY_CORE_MAX];
	u8 i;

	memset((u8 *) cmplx_pwr_dbm, 0, sizeof(cmplx_pwr_dbm));
	wlc_phy_compute_dB(cmplx_pwr, cmplx_pwr_dbm, pi->pubpi.phy_corenum);

	for (i = 0; i < pi->pubpi.phy_corenum; i++) {
		if (NREV_GE(pi->pubpi.phy_rev, 3))
			cmplx_pwr_dbm[i] += (s8) PHY_NOISE_OFFSETFACT_4322;
		else

			cmplx_pwr_dbm[i] += (s8) (16 - (15) * 3 - 70);
	}

	for (i = 0; i < pi->pubpi.phy_corenum; i++) {
		pi->nphy_noise_win[i][pi->nphy_noise_index] = cmplx_pwr_dbm[i];
		pwr_ant[i] = cmplx_pwr_dbm[i];
	}
	pi->nphy_noise_index =
		MODINC_POW2(pi->nphy_noise_index, PHY_NOISE_WINDOW_SZ);
	return true;
}