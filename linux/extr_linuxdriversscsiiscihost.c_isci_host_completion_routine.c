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
typedef  scalar_t__ u16 ;
struct isci_host {TYPE_1__* smu_registers; int /*<<< orphan*/  scic_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_coalesce_control; } ;

/* Variables and functions */
 scalar_t__ ISCI_COALESCE_BASE ; 
 int /*<<< orphan*/  NUMBER ; 
 scalar_t__ SCI_MAX_PORTS ; 
 int SMU_ICC_GEN_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TIMER ; 
 scalar_t__ ilog2 (scalar_t__) ; 
 scalar_t__ isci_tci_active (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_completion_handler (struct isci_host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void isci_host_completion_routine(unsigned long data)
{
	struct isci_host *ihost = (struct isci_host *)data;
	u16 active;

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_completion_handler(ihost);
	spin_unlock_irq(&ihost->scic_lock);

	/*
	 * we subtract SCI_MAX_PORTS to account for the number of dummy TCs
	 * issued for hardware issue workaround
	 */
	active = isci_tci_active(ihost) - SCI_MAX_PORTS;

	/*
	 * the coalesence timeout doubles at each encoding step, so
	 * update it based on the ilog2 value of the outstanding requests
	 */
	writel(SMU_ICC_GEN_VAL(NUMBER, active) |
	       SMU_ICC_GEN_VAL(TIMER, ISCI_COALESCE_BASE + ilog2(active)),
	       &ihost->smu_registers->interrupt_coalesce_control);
}