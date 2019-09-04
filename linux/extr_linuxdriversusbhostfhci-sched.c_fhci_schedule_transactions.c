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
struct fhci_usb {TYPE_1__* hc_list; TYPE_2__* actual_frame; } ;
struct TYPE_4__ {int frame_status; scalar_t__ total_bytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  bulk_list; int /*<<< orphan*/  ctrl_list; int /*<<< orphan*/  intr_list; int /*<<< orphan*/  iso_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FHCI_TF_BULK ; 
 int /*<<< orphan*/  FHCI_TF_CTRL ; 
 int /*<<< orphan*/  FHCI_TF_INTR ; 
 int /*<<< orphan*/  FHCI_TF_ISO ; 
 int FRAME_END_TRANSMISSION ; 
 scalar_t__ rotate_frames (struct fhci_usb*) ; 
 int scan_ed_list (struct fhci_usb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fhci_schedule_transactions(struct fhci_usb *usb)
{
	int left = 1;

	if (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION)
		if (rotate_frames(usb) != 0)
			return;

	if (usb->actual_frame->frame_status & FRAME_END_TRANSMISSION)
		return;

	if (usb->actual_frame->total_bytes == 0) {
		/*
		 * schedule the next available ISO transfer
		 *or next stage of the ISO transfer
		 */
		scan_ed_list(usb, &usb->hc_list->iso_list, FHCI_TF_ISO);

		/*
		 * schedule the next available interrupt transfer or
		 * the next stage of the interrupt transfer
		 */
		scan_ed_list(usb, &usb->hc_list->intr_list, FHCI_TF_INTR);

		/*
		 * schedule the next available control transfer
		 * or the next stage of the control transfer
		 */
		left = scan_ed_list(usb, &usb->hc_list->ctrl_list,
				    FHCI_TF_CTRL);
	}

	/*
	 * schedule the next available bulk transfer or the next stage of the
	 * bulk transfer
	 */
	if (left > 0)
		scan_ed_list(usb, &usb->hc_list->bulk_list, FHCI_TF_BULK);
}