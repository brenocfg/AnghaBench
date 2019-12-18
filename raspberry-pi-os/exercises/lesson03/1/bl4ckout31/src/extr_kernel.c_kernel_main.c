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
 int /*<<< orphan*/  enable_interrupt_controller () ; 
 int /*<<< orphan*/  enable_irq () ; 
 int /*<<< orphan*/  init_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_vector_init () ; 
 int /*<<< orphan*/  local_timer_init () ; 
 int /*<<< orphan*/  putc ; 
 int /*<<< orphan*/  uart_init () ; 
 int /*<<< orphan*/  uart_recv () ; 
 int /*<<< orphan*/  uart_send (int /*<<< orphan*/ ) ; 

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	local_timer_init();
	enable_interrupt_controller();
	enable_irq();

	while (1){
		uart_send(uart_recv());
	}	
}