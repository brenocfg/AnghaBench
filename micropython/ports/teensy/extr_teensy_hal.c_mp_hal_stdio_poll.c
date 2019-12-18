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
 int /*<<< orphan*/ * MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 uintptr_t MP_STREAM_POLL_RD ; 
 int /*<<< orphan*/  pyb_stdio_uart ; 
 scalar_t__ uart_rx_any (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_vcp_rx_num () ; 

uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags) {
    uintptr_t ret = 0;
    if (poll_flags & MP_STREAM_POLL_RD) {
        if (usb_vcp_rx_num()) {
            ret |= MP_STREAM_POLL_RD;
        }
        if (MP_STATE_PORT(pyb_stdio_uart) != NULL && uart_rx_any(MP_STATE_PORT(pyb_stdio_uart))) {
            ret |= MP_STREAM_POLL_RD;
        }
    }
    return ret;
}