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
struct isci_host {int /*<<< orphan*/  completion_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ sci_controller_isr (struct isci_host*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

irqreturn_t isci_msix_isr(int vec, void *data)
{
	struct isci_host *ihost = data;

	if (sci_controller_isr(ihost))
		tasklet_schedule(&ihost->completion_tasklet);

	return IRQ_HANDLED;
}