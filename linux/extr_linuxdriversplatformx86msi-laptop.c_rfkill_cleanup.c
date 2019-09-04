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

/* Variables and functions */
 scalar_t__ rfk_bluetooth ; 
 scalar_t__ rfk_threeg ; 
 scalar_t__ rfk_wlan ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 

__attribute__((used)) static void rfkill_cleanup(void)
{
	if (rfk_bluetooth) {
		rfkill_unregister(rfk_bluetooth);
		rfkill_destroy(rfk_bluetooth);
	}

	if (rfk_threeg) {
		rfkill_unregister(rfk_threeg);
		rfkill_destroy(rfk_threeg);
	}

	if (rfk_wlan) {
		rfkill_unregister(rfk_wlan);
		rfkill_destroy(rfk_wlan);
	}
}