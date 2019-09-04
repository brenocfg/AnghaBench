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
struct scsi_cmnd {int /*<<< orphan*/ * host_scribble; TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  commands; } ;
struct TYPE_3__ {int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 TYPE_2__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ SCDATA (struct scsi_cmnd*) ; 
 struct scsi_cmnd* SCNEXT (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_SC (struct scsi_cmnd**,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,struct scsi_cmnd*) ; 

__attribute__((used)) static void free_hard_reset_SCs(struct Scsi_Host *shpnt,
				struct scsi_cmnd **SCs)
{
	struct scsi_cmnd *ptr;

	ptr=*SCs;
	while(ptr) {
		struct scsi_cmnd *next;

		if(SCDATA(ptr)) {
			next = SCNEXT(ptr);
		} else {
			scmd_printk(KERN_DEBUG, ptr,
				    "queue corrupted at %p\n", ptr);
			next = NULL;
		}

		if (!ptr->device->soft_reset) {
			remove_SC(SCs, ptr);
			HOSTDATA(shpnt)->commands--;
			kfree(ptr->host_scribble);
			ptr->host_scribble=NULL;
		}

		ptr = next;
	}
}