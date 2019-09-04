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
struct mwifiex_adapter {int pm_wakeup_fw_try; int pm_wakeup_card_req; int /*<<< orphan*/  ps_state; int /*<<< orphan*/  wakeup_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_STATE_AWAKE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_pm_wakeup_card(struct mwifiex_adapter *adapter)
{
	/* Simulation of HS_AWAKE event */
	adapter->pm_wakeup_fw_try = false;
	del_timer(&adapter->wakeup_timer);
	adapter->pm_wakeup_card_req = false;
	adapter->ps_state = PS_STATE_AWAKE;

	return 0;
}