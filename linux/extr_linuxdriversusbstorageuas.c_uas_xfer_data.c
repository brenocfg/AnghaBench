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
struct urb {int dummy; } ;
struct uas_cmd_info {unsigned int state; } ;
struct scsi_cmnd {TYPE_1__* device; int /*<<< orphan*/  SCp; } ;
struct TYPE_2__ {int /*<<< orphan*/  hostdata; } ;

/* Variables and functions */
 unsigned int SUBMIT_STATUS_URB ; 
 int /*<<< orphan*/  uas_add_work (struct uas_cmd_info*) ; 
 int uas_submit_urbs (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uas_xfer_data(struct urb *urb, struct scsi_cmnd *cmnd,
			  unsigned direction)
{
	struct uas_cmd_info *cmdinfo = (void *)&cmnd->SCp;
	int err;

	cmdinfo->state |= direction | SUBMIT_STATUS_URB;
	err = uas_submit_urbs(cmnd, cmnd->device->hostdata);
	if (err) {
		uas_add_work(cmdinfo);
	}
}