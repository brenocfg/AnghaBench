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
 int /*<<< orphan*/  AR_MAC_PCU_ASYNC_FIFO_REG3 ; 
 int /*<<< orphan*/  AR_MAC_PCU_ASYNC_FIFO_REG3_DATAPATH_SEL ; 
 int /*<<< orphan*/  AR_MAC_PCU_ASYNC_FIFO_REG3_SOFT_RESET ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int /*<<< orphan*/  AR_PHY_MODE_ASYNCFIFO ; 
 scalar_t__ AR_SREV_9287_13_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9002_hw_enable_async_fifo(struct ath_hw *ah)
{
	if (AR_SREV_9287_13_OR_LATER(ah)) {
		REG_SET_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_DATAPATH_SEL);
		REG_SET_BIT(ah, AR_PHY_MODE, AR_PHY_MODE_ASYNCFIFO);
		REG_CLR_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_SOFT_RESET);
		REG_SET_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_SOFT_RESET);
	}
}