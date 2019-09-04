#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ dev_speed; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_7__ {int /*<<< orphan*/  frame_number; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_SPEED_HIGH ; 
 int dwc_frame_num_inc (int /*<<< orphan*/ ,int) ; 
 int dwc_full_frame_num (int) ; 
 int dwc_micro_frame_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_get_frame_number (TYPE_2__*) ; 

__attribute__((used)) static uint8_t calc_starting_frame(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh,
				   uint8_t * skip_frames)
{
	uint16_t frame = 0;
	hcd->frame_number = dwc_otg_hcd_get_frame_number(hcd);

	/* sched_frame is always frame number(not uFrame) both in FS and HS !! */

	/*
	 * skip_frames is used to limit activated descriptors number
	 * to avoid the situation when HC services the last activated
	 * descriptor firstly.
	 * Example for FS:
	 * Current frame is 1, scheduled frame is 3. Since HC always fetches the descriptor
	 * corresponding to curr_frame+1, the descriptor corresponding to frame 2
	 * will be fetched. If the number of descriptors is max=64 (or greather) the
	 * list will be fully programmed with Active descriptors and it is possible
	 * case(rare) that the latest descriptor(considering rollback) corresponding
	 * to frame 2 will be serviced first. HS case is more probable because, in fact,
	 * up to 11 uframes(16 in the code) may be skipped.
	 */
	if (qh->dev_speed == DWC_OTG_EP_SPEED_HIGH) {
		/*
		 * Consider uframe counter also, to start xfer asap.
		 * If half of the frame elapsed skip 2 frames otherwise
		 * just 1 frame.
		 * Starting descriptor index must be 8-aligned, so
		 * if the current frame is near to complete the next one
		 * is skipped as well.
		 */

		if (dwc_micro_frame_num(hcd->frame_number) >= 5) {
			*skip_frames = 2 * 8;
			frame = dwc_frame_num_inc(hcd->frame_number, *skip_frames);
		} else {
			*skip_frames = 1 * 8;
			frame = dwc_frame_num_inc(hcd->frame_number, *skip_frames);
		}

		frame = dwc_full_frame_num(frame);
	} else {
		/*
		 * Two frames are skipped for FS - the current and the next.
		 * But for descriptor programming, 1 frame(descriptor) is enough,
		 * see example above.
		 */
		*skip_frames = 1;
		frame = dwc_frame_num_inc(hcd->frame_number, 2);
	}

	return frame;
}