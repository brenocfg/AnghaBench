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
struct pqi_ctrl_info {TYPE_1__* registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  sis_host_to_ctrl_doorbell; int /*<<< orphan*/  sis_firmware_status; } ;

/* Variables and functions */
 int SIS_CTRL_KERNEL_PANIC ; 
 int /*<<< orphan*/  SIS_TRIGGER_SHUTDOWN ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sis_shutdown_ctrl(struct pqi_ctrl_info *ctrl_info)
{
	if (readl(&ctrl_info->registers->sis_firmware_status) &
		SIS_CTRL_KERNEL_PANIC)
		return;

	writel(SIS_TRIGGER_SHUTDOWN,
		&ctrl_info->registers->sis_host_to_ctrl_doorbell);
}