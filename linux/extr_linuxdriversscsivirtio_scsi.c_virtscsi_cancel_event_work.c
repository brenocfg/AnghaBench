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
struct TYPE_3__ {int /*<<< orphan*/  vq_lock; } ;
struct virtio_scsi {int stop_events; TYPE_2__* event_list; TYPE_1__ event_vq; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int VIRTIO_SCSI_EVENT_LEN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtscsi_cancel_event_work(struct virtio_scsi *vscsi)
{
	int i;

	/* Stop scheduling work before calling cancel_work_sync.  */
	spin_lock_irq(&vscsi->event_vq.vq_lock);
	vscsi->stop_events = true;
	spin_unlock_irq(&vscsi->event_vq.vq_lock);

	for (i = 0; i < VIRTIO_SCSI_EVENT_LEN; i++)
		cancel_work_sync(&vscsi->event_list[i].work);
}