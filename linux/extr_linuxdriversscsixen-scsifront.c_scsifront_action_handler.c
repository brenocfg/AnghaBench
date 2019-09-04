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
typedef  int /*<<< orphan*/  uint8_t ;
struct vscsifrnt_shadow {int rslt_reset; int wait_reset; int /*<<< orphan*/  rqid; int /*<<< orphan*/  wq_reset; int /*<<< orphan*/  ref_rqid; struct scsi_cmnd* sc; int /*<<< orphan*/  act; } ;
struct vscsifrnt_info {int wait_ring_available; int /*<<< orphan*/  shadow_lock; int /*<<< orphan*/  wq_sync; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int RSLT_RESET_ERR ; 
 int RSLT_RESET_WAITING ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vscsifrnt_shadow*) ; 
 struct vscsifrnt_shadow* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct vscsifrnt_shadow* scsi_cmd_priv (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsifront_do_request (struct vscsifrnt_info*,struct vscsifrnt_shadow*) ; 
 scalar_t__ scsifront_enter (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  scsifront_put_rqid (struct vscsifrnt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsifront_return (struct vscsifrnt_info*) ; 
 struct vscsifrnt_info* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int scsifront_action_handler(struct scsi_cmnd *sc, uint8_t act)
{
	struct Scsi_Host *host = sc->device->host;
	struct vscsifrnt_info *info = shost_priv(host);
	struct vscsifrnt_shadow *shadow, *s = scsi_cmd_priv(sc);
	int err = 0;

	shadow = kzalloc(sizeof(*shadow), GFP_NOIO);
	if (!shadow)
		return FAILED;

	shadow->act = act;
	shadow->rslt_reset = RSLT_RESET_WAITING;
	shadow->sc = sc;
	shadow->ref_rqid = s->rqid;
	init_waitqueue_head(&shadow->wq_reset);

	spin_lock_irq(host->host_lock);

	for (;;) {
		if (scsifront_enter(info))
			goto fail;

		if (!scsifront_do_request(info, shadow))
			break;

		scsifront_return(info);
		if (err)
			goto fail;
		info->wait_ring_available = 1;
		spin_unlock_irq(host->host_lock);
		err = wait_event_interruptible(info->wq_sync,
					       !info->wait_ring_available);
		spin_lock_irq(host->host_lock);
	}

	spin_unlock_irq(host->host_lock);
	err = wait_event_interruptible(shadow->wq_reset, shadow->wait_reset);
	spin_lock_irq(host->host_lock);

	if (!err) {
		err = shadow->rslt_reset;
		scsifront_put_rqid(info, shadow->rqid);
		kfree(shadow);
	} else {
		spin_lock(&info->shadow_lock);
		shadow->rslt_reset = RSLT_RESET_ERR;
		spin_unlock(&info->shadow_lock);
		err = FAILED;
	}

	scsifront_return(info);
	spin_unlock_irq(host->host_lock);
	return err;

fail:
	spin_unlock_irq(host->host_lock);
	kfree(shadow);
	return FAILED;
}