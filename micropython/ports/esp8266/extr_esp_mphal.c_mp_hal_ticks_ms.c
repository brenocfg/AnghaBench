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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ system_time_high_word ; 
 scalar_t__ system_time_low_word ; 
 int /*<<< orphan*/  system_time_update () ; 

uint32_t mp_hal_ticks_ms(void) {
    // Compute milliseconds from 64-bit microsecond counter
    system_time_update();
    return ((uint64_t)system_time_high_word << 32 | (uint64_t)system_time_low_word) / 1000;
}