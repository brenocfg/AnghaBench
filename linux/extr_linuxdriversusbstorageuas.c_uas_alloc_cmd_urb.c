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
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct uas_dev_info {int /*<<< orphan*/  cmd_pipe; struct usb_device* udev; } ;
struct uas_cmd_info {int /*<<< orphan*/  uas_tag; } ;
struct scsi_device {int /*<<< orphan*/  lun; } ;
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  SCp; struct scsi_device* device; } ;
struct command_iu {int len; int /*<<< orphan*/  cdb; int /*<<< orphan*/  lun; int /*<<< orphan*/  prio_attr; int /*<<< orphan*/  tag; int /*<<< orphan*/  iu_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  IU_ID_COMMAND ; 
 int /*<<< orphan*/  UAS_SIMPLE_TAG ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct command_iu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uas_cmd_cmplt ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,struct command_iu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static struct urb *uas_alloc_cmd_urb(struct uas_dev_info *devinfo, gfp_t gfp,
					struct scsi_cmnd *cmnd)
{
	struct usb_device *udev = devinfo->udev;
	struct scsi_device *sdev = cmnd->device;
	struct uas_cmd_info *cmdinfo = (void *)&cmnd->SCp;
	struct urb *urb = usb_alloc_urb(0, gfp);
	struct command_iu *iu;
	int len;

	if (!urb)
		goto out;

	len = cmnd->cmd_len - 16;
	if (len < 0)
		len = 0;
	len = ALIGN(len, 4);
	iu = kzalloc(sizeof(*iu) + len, gfp);
	if (!iu)
		goto free;

	iu->iu_id = IU_ID_COMMAND;
	iu->tag = cpu_to_be16(cmdinfo->uas_tag);
	iu->prio_attr = UAS_SIMPLE_TAG;
	iu->len = len;
	int_to_scsilun(sdev->lun, &iu->lun);
	memcpy(iu->cdb, cmnd->cmnd, cmnd->cmd_len);

	usb_fill_bulk_urb(urb, udev, devinfo->cmd_pipe, iu, sizeof(*iu) + len,
							uas_cmd_cmplt, NULL);
	urb->transfer_flags |= URB_FREE_BUFFER;
 out:
	return urb;
 free:
	usb_free_urb(urb);
	return NULL;
}