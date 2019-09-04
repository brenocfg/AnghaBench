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
typedef  scalar_t__ u32 ;
struct ath9k_hw_mci {scalar_t__ rx_msg_intr; scalar_t__ raw_intr; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */

void ar9003_mci_get_interrupt(struct ath_hw *ah, u32 *raw_intr,
			      u32 *rx_msg_intr)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	*raw_intr = mci->raw_intr;
	*rx_msg_intr = mci->rx_msg_intr;

	/* Clean int bits after the values are read. */
	mci->raw_intr = 0;
	mci->rx_msg_intr = 0;
}