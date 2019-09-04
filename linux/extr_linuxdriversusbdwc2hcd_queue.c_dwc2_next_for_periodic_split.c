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
typedef  scalar_t__ u16 ;
struct dwc2_qh {scalar_t__ next_active_frame; scalar_t__ start_active_frame; scalar_t__ ep_type; int /*<<< orphan*/  ep_is_in; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 void* dwc2_frame_num_dec (scalar_t__,int) ; 
 scalar_t__ dwc2_frame_num_gt (scalar_t__,scalar_t__) ; 
 scalar_t__ dwc2_frame_num_inc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dwc2_next_for_periodic_split(struct dwc2_hsotg *hsotg,
					struct dwc2_qh *qh, u16 frame_number)
{
	u16 old_frame = qh->next_active_frame;
	u16 prev_frame_number = dwc2_frame_num_dec(frame_number, 1);
	int missed = 0;
	u16 incr;

	/*
	 * See dwc2_uframe_schedule_split() for split scheduling.
	 *
	 * Basically: increment 1 normally, but 2 right after the start split
	 * (except for ISOC out).
	 */
	if (old_frame == qh->start_active_frame &&
	    !(qh->ep_type == USB_ENDPOINT_XFER_ISOC && !qh->ep_is_in))
		incr = 2;
	else
		incr = 1;

	qh->next_active_frame = dwc2_frame_num_inc(old_frame, incr);

	/*
	 * Note that it's OK for frame_number to be 1 frame past
	 * next_active_frame.  Remember that next_active_frame is supposed to
	 * be 1 frame _before_ when we want to be scheduled.  If we're 1 frame
	 * past it just means schedule ASAP.
	 *
	 * It's _not_ OK, however, if we're more than one frame past.
	 */
	if (dwc2_frame_num_gt(prev_frame_number, qh->next_active_frame)) {
		/*
		 * OOPS, we missed.  That's actually pretty bad since
		 * the hub will be unhappy; try ASAP I guess.
		 */
		missed = dwc2_frame_num_dec(prev_frame_number,
					    qh->next_active_frame);
		qh->next_active_frame = frame_number;
	}

	return missed;
}