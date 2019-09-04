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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  txEndToXpaOff; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL ; 
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL_TX_END_XPAA_OFF ; 
 int /*<<< orphan*/  AR_PHY_XPA_TIMING_CTL_TX_END_XPAB_OFF ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ar9003_modal_header (struct ath_hw*,int) ; 

__attribute__((used)) static void ar9003_hw_txend_to_xpa_off_apply(struct ath_hw *ah, bool is2ghz)
{
	u32 value;

	value = ar9003_modal_header(ah, is2ghz)->txEndToXpaOff;

	REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
		      AR_PHY_XPA_TIMING_CTL_TX_END_XPAB_OFF, value);
	REG_RMW_FIELD(ah, AR_PHY_XPA_TIMING_CTL,
		      AR_PHY_XPA_TIMING_CTL_TX_END_XPAA_OFF, value);
}