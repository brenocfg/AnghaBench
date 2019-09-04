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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_dev; } ;
struct AdapterControlBlock {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  arcmsr_sysfs_message_clear_attr ; 
 int /*<<< orphan*/  arcmsr_sysfs_message_read_attr ; 
 int /*<<< orphan*/  arcmsr_sysfs_message_write_attr ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void arcmsr_free_sysfs_attr(struct AdapterControlBlock *acb)
{
	struct Scsi_Host *host = acb->host;

	sysfs_remove_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_clear_attr);
	sysfs_remove_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_write_attr);
	sysfs_remove_bin_file(&host->shost_dev.kobj, &arcmsr_sysfs_message_read_attr);
}