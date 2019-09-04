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
struct usb_interface {int dummy; } ;
struct uas_dev_info {int resetting; int /*<<< orphan*/  data_urbs; int /*<<< orphan*/  sense_urbs; int /*<<< orphan*/  cmd_urbs; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uas_free_streams (struct uas_dev_info*) ; 
 int /*<<< orphan*/  uas_zap_pending (struct uas_dev_info*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uas_disconnect(struct usb_interface *intf)
{
	struct Scsi_Host *shost = usb_get_intfdata(intf);
	struct uas_dev_info *devinfo = (struct uas_dev_info *)shost->hostdata;
	unsigned long flags;

	spin_lock_irqsave(&devinfo->lock, flags);
	devinfo->resetting = 1;
	spin_unlock_irqrestore(&devinfo->lock, flags);

	cancel_work_sync(&devinfo->work);
	usb_kill_anchored_urbs(&devinfo->cmd_urbs);
	usb_kill_anchored_urbs(&devinfo->sense_urbs);
	usb_kill_anchored_urbs(&devinfo->data_urbs);
	uas_zap_pending(devinfo, DID_NO_CONNECT);

	scsi_remove_host(shost);
	uas_free_streams(devinfo);
	scsi_host_put(shost);
}