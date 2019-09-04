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
 int /*<<< orphan*/  pyb_stdio_uart ; 
 int /*<<< orphan*/  uart_tx_strn (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ usb_vcp_is_enabled () ; 
 int /*<<< orphan*/  usb_vcp_send_strn (char const*,size_t) ; 

void mp_hal_stdout_tx_strn(const char *str, size_t len) {
    if (MP_STATE_PORT(pyb_stdio_uart) != NULL) {
        uart_tx_strn(MP_STATE_PORT(pyb_stdio_uart), str, len);
    }
    if (usb_vcp_is_enabled()) {
        usb_vcp_send_strn(str, len);
    }
}