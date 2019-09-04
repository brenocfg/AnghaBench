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
 int /*<<< orphan*/  OCTEON_IRQ_TIMER1 ; 
 int /*<<< orphan*/  cvm_oct_device ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvm_oct_tx_shutdown(void)
{
	/* Free the interrupt handler */
	free_irq(OCTEON_IRQ_TIMER1, cvm_oct_device);
}