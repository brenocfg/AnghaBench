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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_DEVICE_RESET ; 
 int ahc_linux_queue_recovery_cmd (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int
ahc_linux_dev_reset(struct scsi_cmnd *cmd)
{
	int error;

	error = ahc_linux_queue_recovery_cmd(cmd, SCB_DEVICE_RESET);
	if (error != 0)
		printk("aic7xxx_dev_reset returns 0x%x\n", error);
	return (error);
}