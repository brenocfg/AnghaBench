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
struct scsi_cmnd {int /*<<< orphan*/  retries; int /*<<< orphan*/ * cmnd; TYPE_2__* device; } ;
struct megasas_instance {TYPE_1__* pdev; int /*<<< orphan*/  adprecovery; } ;
struct TYPE_6__ {scalar_t__ hostdata; } ;
struct TYPE_5__ {TYPE_3__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 scalar_t__ MEGASAS_HW_CRITICAL_ERROR ; 
 int SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int megasas_wait_for_outstanding (struct megasas_instance*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int megasas_generic_reset(struct scsi_cmnd *scmd)
{
	int ret_val;
	struct megasas_instance *instance;

	instance = (struct megasas_instance *)scmd->device->host->hostdata;

	scmd_printk(KERN_NOTICE, scmd, "megasas: RESET cmd=%x retries=%x\n",
		 scmd->cmnd[0], scmd->retries);

	if (atomic_read(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) {
		dev_err(&instance->pdev->dev, "cannot recover from previous reset failures\n");
		return FAILED;
	}

	ret_val = megasas_wait_for_outstanding(instance);
	if (ret_val == SUCCESS)
		dev_notice(&instance->pdev->dev, "reset successful\n");
	else
		dev_err(&instance->pdev->dev, "failed to do reset\n");

	return ret_val;
}