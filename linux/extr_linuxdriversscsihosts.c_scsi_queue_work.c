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
struct work_struct {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  work_q; TYPE_1__* hostt; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dump_stack () ; 
 int queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int scsi_queue_work(struct Scsi_Host *shost, struct work_struct *work)
{
	if (unlikely(!shost->work_q)) {
		shost_printk(KERN_ERR, shost,
			"ERROR: Scsi host '%s' attempted to queue scsi-work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();

		return -EINVAL;
	}

	return queue_work(shost->work_q, work);
}