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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_PHY_TEST ; 
 int /*<<< orphan*/  PHY_AGC_CLR ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_tx99_stop(struct ath_hw *ah)
{
	REG_CLR_BIT(ah, AR_PHY_TEST, PHY_AGC_CLR);
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_DIS);
}