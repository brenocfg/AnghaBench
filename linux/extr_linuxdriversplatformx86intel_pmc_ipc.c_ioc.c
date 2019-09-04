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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_complete; scalar_t__ ipc_base; scalar_t__ irq_mode; } ;

/* Variables and functions */
 scalar_t__ IPC_STATUS ; 
 int IPC_STATUS_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int ipc_read_status () ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ioc(int irq, void *dev_id)
{
	int status;

	if (ipcdev.irq_mode) {
		status = ipc_read_status();
		writel(status | IPC_STATUS_IRQ, ipcdev.ipc_base + IPC_STATUS);
	}
	complete(&ipcdev.cmd_complete);

	return IRQ_HANDLED;
}