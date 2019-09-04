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
 unsigned int AUX_IRQ ; 
 int /*<<< orphan*/  IRQ_PENDING_1 ; 
 unsigned int SYSTEM_TIMER_IRQ_1 ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_timer_irq () ; 
 int /*<<< orphan*/  handle_uart_irq () ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

void handle_irq(void)
{
	unsigned int irq = get32(IRQ_PENDING_1);

	// loop in case multiple interrupts have been raised
	while (irq) {
		// each bitflag is only 1 bit so we do not 
		// need to test equality against themself
		if (irq & SYSTEM_TIMER_IRQ_1) {
			handle_timer_irq();
			irq &= ~SYSTEM_TIMER_IRQ_1;
		} else if (irq & AUX_IRQ) {
			handle_uart_irq();
			irq &= ~AUX_IRQ;
		} else {
			printf("Unknown pending irq: %x\r\n", irq);
			irq = 0;
		}
	}
}