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
 int copy_process (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  enable_interrupt_controller () ; 
 int /*<<< orphan*/  enable_irq () ; 
 int /*<<< orphan*/  init_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_vector_init () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  process ; 
 int /*<<< orphan*/  putc ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  timer_init () ; 
 int /*<<< orphan*/  uart_init () ; 

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}