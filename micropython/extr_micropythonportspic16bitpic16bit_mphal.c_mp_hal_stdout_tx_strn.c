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
 int /*<<< orphan*/  uart_tx_char (int /*<<< orphan*/ ) ; 

void mp_hal_stdout_tx_strn(const char *str, size_t len) {
    for (; len > 0; --len) {
        uart_tx_char(*str++);
    }
}