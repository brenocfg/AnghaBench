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
typedef  int mp_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  __WFI () ; 
 scalar_t__ systick_ms ; 

void mp_hal_delay_us(mp_uint_t us) {
    uint32_t ms = us / 1000 + 1;
    uint32_t t0 = systick_ms;
    while (systick_ms - t0 < ms) {
        __WFI();
    }
}