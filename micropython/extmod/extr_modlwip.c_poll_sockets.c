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
 int /*<<< orphan*/  MICROPY_EVENT_POLL_HOOK ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int) ; 

__attribute__((used)) static inline void poll_sockets(void) {
#ifdef MICROPY_EVENT_POLL_HOOK
    MICROPY_EVENT_POLL_HOOK;
#else
    mp_hal_delay_ms(1);
#endif
}