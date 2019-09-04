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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct brcms_hardware {int hw_stf_ss_opmode; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BRCMS_PHY_11N_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRCM_RATE_12M ; 
 int /*<<< orphan*/  BRCM_RATE_18M ; 
 int /*<<< orphan*/  BRCM_RATE_24M ; 
 int /*<<< orphan*/  BRCM_RATE_36M ; 
 int /*<<< orphan*/  BRCM_RATE_48M ; 
 int /*<<< orphan*/  BRCM_RATE_54M ; 
 int /*<<< orphan*/  BRCM_RATE_6M ; 
 int /*<<< orphan*/  BRCM_RATE_9M ; 
 int M_RT_OFDM_PCTL1_POS ; 
 int PHY_TXC1_MODE_MASK ; 
 int PHY_TXC1_MODE_SHIFT ; 
 int brcms_b_ofdm_ratetable_offset (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int brcms_b_read_shm (struct brcms_hardware*,int) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int,int) ; 

__attribute__((used)) static void brcms_upd_ofdm_pctl1_table(struct brcms_hardware *wlc_hw)
{
	u8 rate;
	u8 rates[8] = {
		BRCM_RATE_6M, BRCM_RATE_9M, BRCM_RATE_12M, BRCM_RATE_18M,
		BRCM_RATE_24M, BRCM_RATE_36M, BRCM_RATE_48M, BRCM_RATE_54M
	};
	u16 entry_ptr;
	u16 pctl1;
	uint i;

	if (!BRCMS_PHY_11N_CAP(wlc_hw->band))
		return;

	/* walk the phy rate table and update the entries */
	for (i = 0; i < ARRAY_SIZE(rates); i++) {
		rate = rates[i];

		entry_ptr = brcms_b_ofdm_ratetable_offset(wlc_hw, rate);

		/* read the SHM Rate Table entry OFDM PCTL1 values */
		pctl1 =
		    brcms_b_read_shm(wlc_hw, entry_ptr + M_RT_OFDM_PCTL1_POS);

		/* modify the value */
		pctl1 &= ~PHY_TXC1_MODE_MASK;
		pctl1 |= (wlc_hw->hw_stf_ss_opmode << PHY_TXC1_MODE_SHIFT);

		/* Update the SHM Rate Table entry OFDM PCTL1 values */
		brcms_b_write_shm(wlc_hw, entry_ptr + M_RT_OFDM_PCTL1_POS,
				   pctl1);
	}
}