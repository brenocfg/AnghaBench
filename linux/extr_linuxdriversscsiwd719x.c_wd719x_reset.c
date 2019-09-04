#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wd719x {TYPE_3__* sh; TYPE_2__* pdev; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  WD719X_CMD_BUSRESET ; 
 int /*<<< orphan*/  WD719X_WAIT_FOR_SCSI_RESET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 struct wd719x* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int wd719x_direct_cmd (struct wd719x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wd719x_reset(struct scsi_cmnd *cmd, u8 opcode, u8 device)
{
	int result;
	unsigned long flags;
	struct wd719x *wd = shost_priv(cmd->device->host);

	dev_info(&wd->pdev->dev, "%s reset requested\n",
		 (opcode == WD719X_CMD_BUSRESET) ? "bus" : "device");

	spin_lock_irqsave(wd->sh->host_lock, flags);
	result = wd719x_direct_cmd(wd, opcode, device, 0, 0, 0,
				   WD719X_WAIT_FOR_SCSI_RESET);
	spin_unlock_irqrestore(wd->sh->host_lock, flags);
	if (result)
		return FAILED;

	return SUCCESS;
}