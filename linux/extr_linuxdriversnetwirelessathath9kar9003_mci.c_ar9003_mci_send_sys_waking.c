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
 int /*<<< orphan*/  MCI_FLAG_DISABLE_TIMESTAMP ; 
 int /*<<< orphan*/  MCI_SYS_WAKING ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ar9003_mci_send_sys_waking(struct ath_hw *ah, bool wait_done)
{
	ar9003_mci_send_message(ah, MCI_SYS_WAKING, MCI_FLAG_DISABLE_TIMESTAMP,
				NULL, 0, wait_done, false);
}