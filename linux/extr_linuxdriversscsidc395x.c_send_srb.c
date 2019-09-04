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
struct ScsiReqBlk {struct DeviceCtlBlk* dcb; } ;
struct DeviceCtlBlk {scalar_t__ max_command; int /*<<< orphan*/  srb_going_list; } ;
struct AdapterCtlBlk {int acb_flag; scalar_t__ active_dcb; } ;

/* Variables and functions */
 int HZ ; 
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 scalar_t__ list_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srb_going_append (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  srb_waiting_append (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  srb_waiting_insert (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  start_scsi (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  waiting_set_timer (struct AdapterCtlBlk*,int) ; 

__attribute__((used)) static void send_srb(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb)
{
	struct DeviceCtlBlk *dcb = srb->dcb;

	if (dcb->max_command <= list_size(&dcb->srb_going_list) ||
	    acb->active_dcb ||
	    (acb->acb_flag & (RESET_DETECT + RESET_DONE + RESET_DEV))) {
		srb_waiting_append(dcb, srb);
		waiting_process_next(acb);
		return;
	}

	if (!start_scsi(acb, dcb, srb))
		srb_going_append(dcb, srb);
	else {
		srb_waiting_insert(dcb, srb);
		waiting_set_timer(acb, HZ / 50);
	}
}