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
 int /*<<< orphan*/  pl011_uart_init () ; 
 int /*<<< orphan*/  pl011_uart_recv () ; 
 int /*<<< orphan*/  pl011_uart_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl011_uart_send_string (char*) ; 

void kernel_main(void)
{
	pl011_uart_init();
	pl011_uart_send_string("Hello, world!\r\n");

	while (1) {
		pl011_uart_send(pl011_uart_recv());
	}
}