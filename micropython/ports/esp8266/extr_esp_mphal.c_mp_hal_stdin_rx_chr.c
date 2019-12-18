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
 int /*<<< orphan*/  ets_loop_iter () ; 
 int /*<<< orphan*/  mp_hal_delay_us (int) ; 
 int ringbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin_ringbuf ; 

int mp_hal_stdin_rx_chr(void) {
    for (;;) {
        int c = ringbuf_get(&stdin_ringbuf);
        if (c != -1) {
            return c;
        }
        #if 0
        // Idles CPU but need more testing before enabling
        if (!ets_loop_iter()) {
            asm("waiti 0");
        }
        #else
        mp_hal_delay_us(1);
        #endif
    }
}