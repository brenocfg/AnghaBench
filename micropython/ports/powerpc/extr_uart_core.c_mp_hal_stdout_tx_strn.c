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
 scalar_t__ lpc_console ; 
 int /*<<< orphan*/  lpc_uart_write (char const) ; 
 scalar_t__ potato_console ; 
 int /*<<< orphan*/  potato_uart_write (char const) ; 

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    if (lpc_console) {
        int i;
        for (i = 0; i < len; i++) {
            lpc_uart_write(str[i]);
        }
    } else if (potato_console) {
        int i;
        for (i = 0; i < len; i++) {
            potato_uart_write(str[i]);
        }
    }
}