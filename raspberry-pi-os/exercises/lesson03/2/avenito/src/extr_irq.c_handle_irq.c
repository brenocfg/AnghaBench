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
 int /*<<< orphan*/  AUX_IRQ ; 
 int /*<<< orphan*/  IRQ_PENDING_1 ; 
 unsigned int SYSTEM_TIMER_IRQ_1 ; 
 unsigned int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_timer_irq () ; 
 int /*<<< orphan*/  handle_uart_irq () ; 
 unsigned int miniUART_IRQ ; 

void handle_irq(void)
{
	unsigned int irq1 = get32(IRQ_PENDING_1);
	unsigned int irq2 = get32(AUX_IRQ);

	if (irq1 & SYSTEM_TIMER_IRQ_1) handle_timer_irq();
	if (irq2 & miniUART_IRQ) handle_uart_irq();
	
}