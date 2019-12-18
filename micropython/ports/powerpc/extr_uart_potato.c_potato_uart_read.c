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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  POTATO_CONSOLE_RX ; 
 int potato_uart_reg_read (int /*<<< orphan*/ ) ; 
 scalar_t__ potato_uart_rx_empty () ; 

char potato_uart_read(void) {
    uint64_t val;

    while (potato_uart_rx_empty());
    val = potato_uart_reg_read(POTATO_CONSOLE_RX);

    return (char)(val & 0x000000ff);
}