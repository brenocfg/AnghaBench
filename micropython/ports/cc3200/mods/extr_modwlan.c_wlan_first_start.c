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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_STATUS_BIT_ALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_LockObjUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sl_Start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_LockObj ; 
 int /*<<< orphan*/  wlan_get_sl_mac () ; 
 TYPE_1__ wlan_obj ; 

void wlan_first_start (void) {
    if (wlan_obj.mode < 0) {
        CLR_STATUS_BIT_ALL(wlan_obj.status);
        wlan_obj.mode = sl_Start(0, 0, 0);
        #ifdef SL_PLATFORM_MULTI_THREADED
        sl_LockObjUnlock (&wlan_LockObj);
        #endif
    }

    // get the mac address
    wlan_get_sl_mac();
}