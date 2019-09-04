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
 scalar_t__ rfk_bluetooth ; 
 scalar_t__ rfk_threeg ; 
 scalar_t__ rfk_wlan ; 
 int /*<<< orphan*/  rfkill_bluetooth_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (scalar_t__,int) ; 
 int /*<<< orphan*/  rfkill_threeg_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rfkill_wlan_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  threeg_s ; 
 int /*<<< orphan*/  wlan_s ; 

__attribute__((used)) static void msi_init_rfkill(struct work_struct *ignored)
{
	if (rfk_wlan) {
		rfkill_set_sw_state(rfk_wlan, !wlan_s);
		rfkill_wlan_set(NULL, !wlan_s);
	}
	if (rfk_bluetooth) {
		rfkill_set_sw_state(rfk_bluetooth, !bluetooth_s);
		rfkill_bluetooth_set(NULL, !bluetooth_s);
	}
	if (rfk_threeg) {
		rfkill_set_sw_state(rfk_threeg, !threeg_s);
		rfkill_threeg_set(NULL, !threeg_s);
	}
}