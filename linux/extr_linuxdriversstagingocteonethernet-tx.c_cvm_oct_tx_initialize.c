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
 int /*<<< orphan*/  CVMX_CIU_TIMX (int) ; 
 int /*<<< orphan*/  OCTEON_IRQ_TIMER1 ; 
 int /*<<< orphan*/  cvm_oct_device ; 
 int /*<<< orphan*/  cvm_oct_tx_cleanup_watchdog ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void cvm_oct_tx_initialize(void)
{
	int i;

	/* Disable the interrupt.  */
	cvmx_write_csr(CVMX_CIU_TIMX(1), 0);
	/* Register an IRQ handler to receive CIU_TIMX(1) interrupts */
	i = request_irq(OCTEON_IRQ_TIMER1,
			cvm_oct_tx_cleanup_watchdog, 0,
			"Ethernet", cvm_oct_device);

	if (i)
		panic("Could not acquire Ethernet IRQ %d\n", OCTEON_IRQ_TIMER1);
}