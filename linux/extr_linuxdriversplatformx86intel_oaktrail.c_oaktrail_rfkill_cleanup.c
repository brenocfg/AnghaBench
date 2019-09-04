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
 int /*<<< orphan*/  __oaktrail_rfkill_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_rfkill ; 
 int /*<<< orphan*/  gps_rfkill ; 
 int /*<<< orphan*/  wifi_rfkill ; 
 int /*<<< orphan*/  wwan_rfkill ; 

__attribute__((used)) static void oaktrail_rfkill_cleanup(void)
{
	__oaktrail_rfkill_cleanup(wifi_rfkill);
	__oaktrail_rfkill_cleanup(bt_rfkill);
	__oaktrail_rfkill_cleanup(gps_rfkill);
	__oaktrail_rfkill_cleanup(wwan_rfkill);
}