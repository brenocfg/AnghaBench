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
typedef  scalar_t__ mp_uint_t ;

/* Variables and functions */
 scalar_t__ mp_hal_ticks_ms () ; 

void mp_hal_delay_ms(mp_uint_t ms) {
    uint32_t start = mp_hal_ticks_ms();
    while (mp_hal_ticks_ms() - start < ms) {
    }
}