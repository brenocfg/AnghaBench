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
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 scalar_t__ EF4_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EF4_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_BZ_RX_INGR_EN ; 
 int /*<<< orphan*/  FR_AZ_RX_CFG ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_drain_tx_fifo (struct ef4_nic*) ; 

__attribute__((used)) static void falcon_deconfigure_mac_wrapper(struct ef4_nic *efx)
{
	ef4_oword_t reg;

	if (ef4_nic_rev(efx) < EF4_REV_FALCON_B0)
		return;

	/* Isolate the MAC -> RX */
	ef4_reado(efx, &reg, FR_AZ_RX_CFG);
	EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, 0);
	ef4_writeo(efx, &reg, FR_AZ_RX_CFG);

	/* Isolate TX -> MAC */
	falcon_drain_tx_fifo(efx);
}