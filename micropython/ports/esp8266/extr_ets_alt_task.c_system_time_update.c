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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ets_intr_lock () ; 
 int /*<<< orphan*/  ets_intr_unlock () ; 
 scalar_t__ system_get_time () ; 
 int system_time_high_word ; 
 scalar_t__ system_time_low_word ; 

void system_time_update(void) {
    // Handle overflow of system microsecond counter
    ets_intr_lock();
    uint32_t system_time_cur = system_get_time();
    if (system_time_cur < system_time_low_word) {
        system_time_high_word += 1; // record overflow of low 32-bits
    }
    system_time_low_word = system_time_cur;
    ets_intr_unlock();
}