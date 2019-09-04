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
struct scsi_event {int dummy; } ;
struct scsi_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum scsi_device_event { ____Placeholder_scsi_device_event } scsi_device_event ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 struct scsi_event* sdev_evt_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_evt_send (struct scsi_device*,struct scsi_event*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int) ; 

void sdev_evt_send_simple(struct scsi_device *sdev,
			  enum scsi_device_event evt_type, gfp_t gfpflags)
{
	struct scsi_event *evt = sdev_evt_alloc(evt_type, gfpflags);
	if (!evt) {
		sdev_printk(KERN_ERR, sdev, "event %d eaten due to OOM\n",
			    evt_type);
		return;
	}

	sdev_evt_send(sdev, evt);
}