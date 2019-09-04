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
struct device {int /*<<< orphan*/  parent; } ;
struct scsi_target {scalar_t__ state; int /*<<< orphan*/  siblings; struct device dev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; TYPE_1__* hostt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* target_destroy ) (struct scsi_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ STARGET_DEL ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_target*) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 

__attribute__((used)) static void scsi_target_destroy(struct scsi_target *starget)
{
	struct device *dev = &starget->dev;
	struct Scsi_Host *shost = dev_to_shost(dev->parent);
	unsigned long flags;

	BUG_ON(starget->state == STARGET_DEL);
	starget->state = STARGET_DEL;
	transport_destroy_device(dev);
	spin_lock_irqsave(shost->host_lock, flags);
	if (shost->hostt->target_destroy)
		shost->hostt->target_destroy(starget);
	list_del_init(&starget->siblings);
	spin_unlock_irqrestore(shost->host_lock, flags);
	put_device(dev);
}