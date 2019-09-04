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
typedef  int /*<<< orphan*/  u32 ;
struct vhost_scsi_tpg {int tport_tpgt; } ;
struct TYPE_2__ {int* lun; } ;
struct vhost_scsi_evt {int /*<<< orphan*/  list; TYPE_1__ event; } ;
struct vhost_scsi {int /*<<< orphan*/  vs_event_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  vs_event_list; } ;
struct se_lun {int unpacked_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vhost_scsi_evt* vhost_scsi_allocate_evt (struct vhost_scsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_work_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vhost_scsi_send_evt(struct vhost_scsi *vs,
		   struct vhost_scsi_tpg *tpg,
		   struct se_lun *lun,
		   u32 event,
		   u32 reason)
{
	struct vhost_scsi_evt *evt;

	evt = vhost_scsi_allocate_evt(vs, event, reason);
	if (!evt)
		return;

	if (tpg && lun) {
		/* TODO: share lun setup code with virtio-scsi.ko */
		/*
		 * Note: evt->event is zeroed when we allocate it and
		 * lun[4-7] need to be zero according to virtio-scsi spec.
		 */
		evt->event.lun[0] = 0x01;
		evt->event.lun[1] = tpg->tport_tpgt;
		if (lun->unpacked_lun >= 256)
			evt->event.lun[2] = lun->unpacked_lun >> 8 | 0x40 ;
		evt->event.lun[3] = lun->unpacked_lun & 0xFF;
	}

	llist_add(&evt->list, &vs->vs_event_list);
	vhost_work_queue(&vs->dev, &vs->vs_event_work);
}