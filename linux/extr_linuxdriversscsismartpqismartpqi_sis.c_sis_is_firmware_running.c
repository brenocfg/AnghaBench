#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pqi_ctrl_info {TYPE_2__* registers; TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sis_mailbox; int /*<<< orphan*/  sis_firmware_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SIS_CTRL_KERNEL_PANIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int readl (int /*<<< orphan*/ *) ; 

bool sis_is_firmware_running(struct pqi_ctrl_info *ctrl_info)
{
	bool running;
	u32 status;

	status = readl(&ctrl_info->registers->sis_firmware_status);

	if (status & SIS_CTRL_KERNEL_PANIC)
		running = false;
	else
		running = true;

	if (!running)
		dev_err(&ctrl_info->pci_dev->dev,
			"controller is offline: status code 0x%x\n",
			readl(&ctrl_info->registers->sis_mailbox[7]));

	return running;
}