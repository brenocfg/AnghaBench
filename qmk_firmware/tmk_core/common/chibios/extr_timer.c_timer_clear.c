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
 int /*<<< orphan*/  chVTGetSystemTime () ; 
 scalar_t__ current_time_ms ; 
 int /*<<< orphan*/  last_systime ; 
 scalar_t__ overflow ; 

void timer_clear(void) {
    last_systime    = chVTGetSystemTime();
    overflow        = 0;
    current_time_ms = 0;
}