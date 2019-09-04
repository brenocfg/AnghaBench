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
struct TYPE_2__ {int alarmset; } ;

/* Variables and functions */
 int /*<<< orphan*/  pyb_rtc_disable_interupt () ; 
 TYPE_1__ pyb_rtc_obj ; 

void pyb_rtc_disable_alarm (void) {
    pyb_rtc_obj.alarmset = false;
    pyb_rtc_disable_interupt();
}