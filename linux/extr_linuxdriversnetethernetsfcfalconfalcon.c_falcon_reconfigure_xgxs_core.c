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
struct ef4_nic {scalar_t__ loopback_mode; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int EF4_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FFE_AB_XX_FORCE_SIG_ALL_LANES ; 
 int /*<<< orphan*/  FRF_AB_XX_FORCE_SIG ; 
 int /*<<< orphan*/  FRF_AB_XX_LPBKA ; 
 int /*<<< orphan*/  FRF_AB_XX_LPBKB ; 
 int /*<<< orphan*/  FRF_AB_XX_LPBKC ; 
 int /*<<< orphan*/  FRF_AB_XX_LPBKD ; 
 int /*<<< orphan*/  FRF_AB_XX_XGMII_LB_EN ; 
 int /*<<< orphan*/  FRF_AB_XX_XGXS_LB_EN ; 
 int /*<<< orphan*/  FR_AB_XX_CORE_STAT ; 
 int /*<<< orphan*/  FR_AB_XX_SD_CTL ; 
 scalar_t__ LOOPBACK_XAUI ; 
 scalar_t__ LOOPBACK_XGMII ; 
 scalar_t__ LOOPBACK_XGXS ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_reset_xaui (struct ef4_nic*) ; 

__attribute__((used)) static void falcon_reconfigure_xgxs_core(struct ef4_nic *efx)
{
	ef4_oword_t reg;
	bool xgxs_loopback = (efx->loopback_mode == LOOPBACK_XGXS);
	bool xaui_loopback = (efx->loopback_mode == LOOPBACK_XAUI);
	bool xgmii_loopback = (efx->loopback_mode == LOOPBACK_XGMII);
	bool old_xgmii_loopback, old_xgxs_loopback, old_xaui_loopback;

	/* XGXS block is flaky and will need to be reset if moving
	 * into our out of XGMII, XGXS or XAUI loopbacks. */
	ef4_reado(efx, &reg, FR_AB_XX_CORE_STAT);
	old_xgxs_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_XGXS_LB_EN);
	old_xgmii_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_XGMII_LB_EN);

	ef4_reado(efx, &reg, FR_AB_XX_SD_CTL);
	old_xaui_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_LPBKA);

	/* The PHY driver may have turned XAUI off */
	if ((xgxs_loopback != old_xgxs_loopback) ||
	    (xaui_loopback != old_xaui_loopback) ||
	    (xgmii_loopback != old_xgmii_loopback))
		falcon_reset_xaui(efx);

	ef4_reado(efx, &reg, FR_AB_XX_CORE_STAT);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_FORCE_SIG,
			    (xgxs_loopback || xaui_loopback) ?
			    FFE_AB_XX_FORCE_SIG_ALL_LANES : 0);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_XGXS_LB_EN, xgxs_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_XGMII_LB_EN, xgmii_loopback);
	ef4_writeo(efx, &reg, FR_AB_XX_CORE_STAT);

	ef4_reado(efx, &reg, FR_AB_XX_SD_CTL);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKD, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKC, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKB, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKA, xaui_loopback);
	ef4_writeo(efx, &reg, FR_AB_XX_SD_CTL);
}