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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __WFI () ; 
 int /*<<< orphan*/  systick_has_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void systick_wait_at_least(uint32_t start_tick, uint32_t delay_ms) {
    while (!systick_has_passed(start_tick, delay_ms)) {
        __WFI(); // enter sleep mode, waiting for interrupt
    }
}