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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RTT_SW_RTT_TABLE_ACCESS ; 
 int /*<<< orphan*/  AR_PHY_RTT_SW_RTT_TABLE_ADDR ; 
 int /*<<< orphan*/  AR_PHY_RTT_SW_RTT_TABLE_DATA ; 
 int /*<<< orphan*/  AR_PHY_RTT_SW_RTT_TABLE_WRITE ; 
 int /*<<< orphan*/  AR_PHY_RTT_TABLE_SW_INTF_1_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_RTT_TABLE_SW_INTF_B (int /*<<< orphan*/ ) ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTT_ACCESS_TIMEOUT ; 
 int RTT_BAD_VALUE ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ar9003_hw_rtt_fill_hist_entry(struct ath_hw *ah, u8 chain, u32 index)
{
	u32 val;

	val = SM(0, AR_PHY_RTT_SW_RTT_TABLE_ACCESS) |
	      SM(0, AR_PHY_RTT_SW_RTT_TABLE_WRITE) |
	      SM(index, AR_PHY_RTT_SW_RTT_TABLE_ADDR);

	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	val |= SM(1, AR_PHY_RTT_SW_RTT_TABLE_ACCESS);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	if (!ath9k_hw_wait(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain),
			   AR_PHY_RTT_SW_RTT_TABLE_ACCESS, 0,
			   RTT_ACCESS_TIMEOUT))
		return RTT_BAD_VALUE;

	val = MS(REG_READ(ah, AR_PHY_RTT_TABLE_SW_INTF_1_B(chain)),
		 AR_PHY_RTT_SW_RTT_TABLE_DATA);


	return val;
}