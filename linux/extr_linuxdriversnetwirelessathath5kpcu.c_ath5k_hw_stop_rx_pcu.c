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
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_DIAG_SW ; 
 int /*<<< orphan*/  AR5K_DIAG_SW_DIS_RX ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ath5k_hw_stop_rx_pcu(struct ath5k_hw *ah)
{
	AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW, AR5K_DIAG_SW_DIS_RX);
}