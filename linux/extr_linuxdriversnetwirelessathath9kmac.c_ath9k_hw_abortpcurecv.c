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
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_disable_mib_counters (struct ath_hw*) ; 

void ath9k_hw_abortpcurecv(struct ath_hw *ah)
{
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_ABORT | AR_DIAG_RX_DIS);

	ath9k_hw_disable_mib_counters(ah);
}