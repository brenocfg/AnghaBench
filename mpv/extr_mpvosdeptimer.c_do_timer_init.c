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
 scalar_t__ MP_START_TIME ; 
 int /*<<< orphan*/  mp_raw_time_init () ; 
 int /*<<< orphan*/  mp_raw_time_us () ; 
 int /*<<< orphan*/  raw_time_offset ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_timer_init(void)
{
    mp_raw_time_init();
    srand(mp_raw_time_us());
    raw_time_offset = mp_raw_time_us();
    // Arbitrary additional offset to avoid confusing relative/absolute times.
    // Also,we rule that the timer never returns 0 (so default-initialized
    // time values will be always in the past).
    raw_time_offset -= MP_START_TIME;
}