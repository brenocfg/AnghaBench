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
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  stream_id; } ;
struct uas_dev_info {scalar_t__ use_streams; int /*<<< orphan*/  status_pipe; struct usb_device* udev; } ;
struct uas_cmd_info {int /*<<< orphan*/  uas_tag; } ;
struct sense_iu {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; int /*<<< orphan*/  SCp; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 struct sense_iu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uas_stat_cmplt ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,struct sense_iu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static struct urb *uas_alloc_sense_urb(struct uas_dev_info *devinfo, gfp_t gfp,
				       struct scsi_cmnd *cmnd)
{
	struct usb_device *udev = devinfo->udev;
	struct uas_cmd_info *cmdinfo = (void *)&cmnd->SCp;
	struct urb *urb = usb_alloc_urb(0, gfp);
	struct sense_iu *iu;

	if (!urb)
		goto out;

	iu = kzalloc(sizeof(*iu), gfp);
	if (!iu)
		goto free;

	usb_fill_bulk_urb(urb, udev, devinfo->status_pipe, iu, sizeof(*iu),
			  uas_stat_cmplt, cmnd->device->host);
	if (devinfo->use_streams)
		urb->stream_id = cmdinfo->uas_tag;
	urb->transfer_flags |= URB_FREE_BUFFER;
 out:
	return urb;
 free:
	usb_free_urb(urb);
	return NULL;
}