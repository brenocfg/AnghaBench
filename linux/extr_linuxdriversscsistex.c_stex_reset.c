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
struct st_hba {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hostdata; } ;
struct TYPE_3__ {TYPE_2__* host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 scalar_t__ stex_do_reset (struct st_hba*) ; 

__attribute__((used)) static int stex_reset(struct scsi_cmnd *cmd)
{
	struct st_hba *hba;

	hba = (struct st_hba *) &cmd->device->host->hostdata[0];

	shost_printk(KERN_INFO, cmd->device->host,
		     "resetting host\n");

	return stex_do_reset(hba) ? FAILED : SUCCESS;
}