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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bluetooth_s ; 
 int /*<<< orphan*/  get_wireless_state_ec_standard () ; 
 int /*<<< orphan*/  msi_rfkill_set_state (scalar_t__,int) ; 
 scalar_t__ rfk_bluetooth ; 
 scalar_t__ rfk_threeg ; 
 scalar_t__ rfk_wlan ; 
 int /*<<< orphan*/  threeg_s ; 
 int /*<<< orphan*/  wlan_s ; 

__attribute__((used)) static void msi_update_rfkill(struct work_struct *ignored)
{
	get_wireless_state_ec_standard();

	if (rfk_wlan)
		msi_rfkill_set_state(rfk_wlan, !wlan_s);
	if (rfk_bluetooth)
		msi_rfkill_set_state(rfk_bluetooth, !bluetooth_s);
	if (rfk_threeg)
		msi_rfkill_set_state(rfk_threeg, !threeg_s);
}