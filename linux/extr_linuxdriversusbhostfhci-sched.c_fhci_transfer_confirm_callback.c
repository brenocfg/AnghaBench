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
typedef  int /*<<< orphan*/  u32 ;
struct fhci_hcd {TYPE_1__* process_done_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (TYPE_1__*) ; 

u32 fhci_transfer_confirm_callback(struct fhci_hcd *fhci)
{
	if (!fhci->process_done_task->state)
		tasklet_schedule(fhci->process_done_task);
	return 0;
}