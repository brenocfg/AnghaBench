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
 int /*<<< orphan*/  ets_event_poll () ; 
 scalar_t__ system_get_time () ; 

void mp_hal_delay_us(uint32_t us) {
    uint32_t start = system_get_time();
    while (system_get_time() - start < us) {
        ets_event_poll();
    }
}