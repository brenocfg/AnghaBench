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
typedef  scalar_t__ u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_D_GBL_IFS_SIFS ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ath9k_hw_mac_to_clks (struct ath_hw*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ath9k_hw_set_sifs_time(struct ath_hw *ah, u32 us)
{
	u32 val = ath9k_hw_mac_to_clks(ah, us - 2);
	val = min(val, (u32) 0xFFFF);
	REG_WRITE(ah, AR_D_GBL_IFS_SIFS, val);
}