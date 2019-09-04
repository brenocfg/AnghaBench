#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioa_host_interrupt_clr_reg; int /*<<< orphan*/  ioa_host_interrupt_mask_reg; } ;
struct pmcraid_instance {TYPE_1__ int_regs; int /*<<< orphan*/  interrupt_mode; } ;

/* Variables and functions */
 int INTRS_TRANSITION_TO_OPERATIONAL ; 
 int /*<<< orphan*/  PMCRAID_PCI_INTERRUPTS ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_enable_interrupts (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int pmcraid_read_interrupts (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_reinit_buffers (struct pmcraid_instance*) ; 

__attribute__((used)) static int pmcraid_reset_enable_ioa(struct pmcraid_instance *pinstance)
{
	u32 intrs;

	pmcraid_reinit_buffers(pinstance);
	intrs = pmcraid_read_interrupts(pinstance);

	pmcraid_enable_interrupts(pinstance, PMCRAID_PCI_INTERRUPTS);

	if (intrs & INTRS_TRANSITION_TO_OPERATIONAL) {
		if (!pinstance->interrupt_mode) {
			iowrite32(INTRS_TRANSITION_TO_OPERATIONAL,
				pinstance->int_regs.
				ioa_host_interrupt_mask_reg);
			iowrite32(INTRS_TRANSITION_TO_OPERATIONAL,
				pinstance->int_regs.ioa_host_interrupt_clr_reg);
		}
		return 1;
	} else {
		return 0;
	}
}