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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SL_OS_WAIT_FOREVER ; 
 int /*<<< orphan*/  sl_LockObjLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_LockObj ; 
 int /*<<< orphan*/  wlan_clear_data () ; 
 TYPE_1__ wlan_obj ; 
 int /*<<< orphan*/  wlan_servers_stop () ; 

void wlan_stop (uint32_t timeout) {
    wlan_servers_stop();
    #ifdef SL_PLATFORM_MULTI_THREADED
    sl_LockObjLock (&wlan_LockObj, SL_OS_WAIT_FOREVER);
    #endif
    sl_Stop(timeout);
    wlan_clear_data();
    wlan_obj.mode = -1;
}