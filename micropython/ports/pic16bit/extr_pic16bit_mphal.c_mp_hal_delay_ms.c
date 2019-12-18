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
typedef  int mp_uint_t ;

/* Variables and functions */

void mp_hal_delay_ms(mp_uint_t ms) {
    // tuned for fixed CPU frequency
    for (int i = ms; i > 0; i--) {
        for (volatile int j = 0; j < 5000; j++) {
        }
    }
}