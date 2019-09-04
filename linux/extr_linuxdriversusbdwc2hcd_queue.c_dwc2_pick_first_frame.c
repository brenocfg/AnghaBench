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
typedef  int u16 ;
struct dwc2_qh {scalar_t__ dev_speed; int num_hs_transfers; int ls_start_schedule_slice; int next_active_frame; int start_active_frame; int /*<<< orphan*/  host_interval; TYPE_2__* hs_transfers; scalar_t__ do_split; } ;
struct TYPE_3__ {int /*<<< orphan*/  uframe_sched; } ;
struct dwc2_hsotg {TYPE_1__ params; } ;
struct TYPE_4__ {int start_schedule_us; } ;

/* Variables and functions */
 int DWC2_HS_PERIODIC_US_PER_UFRAME ; 
 int /*<<< orphan*/  DWC2_HS_SCHEDULE_UFRAMES ; 
 int DWC2_LS_PERIODIC_SLICES_PER_FRAME ; 
 int /*<<< orphan*/  DWC2_LS_SCHEDULE_FRAMES ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dwc2_frame_num_dec (int,int) ; 
 scalar_t__ dwc2_frame_num_gt (int,int) ; 
 int dwc2_frame_num_inc (int,int) ; 
 int dwc2_hcd_get_frame_number (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_sch_vdbg (struct dwc2_hsotg*,char*,struct dwc2_qh*,int,int) ; 
 int gcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_pick_first_frame(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	u16 frame_number;
	u16 earliest_frame;
	u16 next_active_frame;
	u16 relative_frame;
	u16 interval;

	/*
	 * Use the real frame number rather than the cached value as of the
	 * last SOF to give us a little extra slop.
	 */
	frame_number = dwc2_hcd_get_frame_number(hsotg);

	/*
	 * We wouldn't want to start any earlier than the next frame just in
	 * case the frame number ticks as we're doing this calculation.
	 *
	 * NOTE: if we could quantify how long till we actually get scheduled
	 * we might be able to avoid the "+ 1" by looking at the upper part of
	 * HFNUM (the FRREM field).  For now we'll just use the + 1 though.
	 */
	earliest_frame = dwc2_frame_num_inc(frame_number, 1);
	next_active_frame = earliest_frame;

	/* Get the "no microframe schduler" out of the way... */
	if (!hsotg->params.uframe_sched) {
		if (qh->do_split)
			/* Splits are active at microframe 0 minus 1 */
			next_active_frame |= 0x7;
		goto exit;
	}

	if (qh->dev_speed == USB_SPEED_HIGH || qh->do_split) {
		/*
		 * We're either at high speed or we're doing a split (which
		 * means we're talking high speed to a hub).  In any case
		 * the first frame should be based on when the first scheduled
		 * event is.
		 */
		WARN_ON(qh->num_hs_transfers < 1);

		relative_frame = qh->hs_transfers[0].start_schedule_us /
				 DWC2_HS_PERIODIC_US_PER_UFRAME;

		/* Adjust interval as per high speed schedule */
		interval = gcd(qh->host_interval, DWC2_HS_SCHEDULE_UFRAMES);

	} else {
		/*
		 * Low or full speed directly on dwc2.  Just about the same
		 * as high speed but on a different schedule and with slightly
		 * different adjustments.  Note that this works because when
		 * the host and device are both low speed then frames in the
		 * controller tick at low speed.
		 */
		relative_frame = qh->ls_start_schedule_slice /
				 DWC2_LS_PERIODIC_SLICES_PER_FRAME;
		interval = gcd(qh->host_interval, DWC2_LS_SCHEDULE_FRAMES);
	}

	/* Scheduler messed up if frame is past interval */
	WARN_ON(relative_frame >= interval);

	/*
	 * We know interval must divide (HFNUM_MAX_FRNUM + 1) now that we've
	 * done the gcd(), so it's safe to move to the beginning of the current
	 * interval like this.
	 *
	 * After this we might be before earliest_frame, but don't worry,
	 * we'll fix it...
	 */
	next_active_frame = (next_active_frame / interval) * interval;

	/*
	 * Actually choose to start at the frame number we've been
	 * scheduled for.
	 */
	next_active_frame = dwc2_frame_num_inc(next_active_frame,
					       relative_frame);

	/*
	 * We actually need 1 frame before since the next_active_frame is
	 * the frame number we'll be put on the ready list and we won't be on
	 * the bus until 1 frame later.
	 */
	next_active_frame = dwc2_frame_num_dec(next_active_frame, 1);

	/*
	 * By now we might actually be before the earliest_frame.  Let's move
	 * up intervals until we're not.
	 */
	while (dwc2_frame_num_gt(earliest_frame, next_active_frame))
		next_active_frame = dwc2_frame_num_inc(next_active_frame,
						       interval);

exit:
	qh->next_active_frame = next_active_frame;
	qh->start_active_frame = next_active_frame;

	dwc2_sch_vdbg(hsotg, "QH=%p First fn=%04x nxt=%04x\n",
		      qh, frame_number, qh->next_active_frame);
}