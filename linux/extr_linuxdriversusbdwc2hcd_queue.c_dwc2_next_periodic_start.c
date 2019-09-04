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
typedef  int u16 ;
struct dwc2_qh {int host_interval; int start_active_frame; int next_active_frame; scalar_t__ dev_speed; scalar_t__ do_split; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int DWC2_HS_SCHEDULE_UFRAMES ; 
 int DWC2_LS_SCHEDULE_FRAMES ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int dwc2_frame_num_dec (int,int) ; 
 scalar_t__ dwc2_frame_num_gt (int,int) ; 
 void* dwc2_frame_num_inc (int,int) ; 
 int gcd (int,int) ; 

__attribute__((used)) static int dwc2_next_periodic_start(struct dwc2_hsotg *hsotg,
				    struct dwc2_qh *qh, u16 frame_number)
{
	int missed = 0;
	u16 interval = qh->host_interval;
	u16 prev_frame_number = dwc2_frame_num_dec(frame_number, 1);

	qh->start_active_frame = dwc2_frame_num_inc(qh->start_active_frame,
						    interval);

	/*
	 * The dwc2_frame_num_gt() function used below won't work terribly well
	 * with if we just incremented by a really large intervals since the
	 * frame counter only goes to 0x3fff.  It's terribly unlikely that we
	 * will have missed in this case anyway.  Just go to exit.  If we want
	 * to try to do better we'll need to keep track of a bigger counter
	 * somewhere in the driver and handle overflows.
	 */
	if (interval >= 0x1000)
		goto exit;

	/*
	 * Test for misses, which is when it's too late to schedule.
	 *
	 * A few things to note:
	 * - We compare against prev_frame_number since start_active_frame
	 *   and next_active_frame are always 1 frame before we want things
	 *   to be active and we assume we can still get scheduled in the
	 *   current frame number.
	 * - It's possible for start_active_frame (now incremented) to be
	 *   next_active_frame if we got an EO MISS (even_odd miss) which
	 *   basically means that we detected there wasn't enough time for
	 *   the last packet and dwc2_hc_set_even_odd_frame() rescheduled us
	 *   at the last second.  We want to make sure we don't schedule
	 *   another transfer for the same frame.  My test webcam doesn't seem
	 *   terribly upset by missing a transfer but really doesn't like when
	 *   we do two transfers in the same frame.
	 * - Some misses are expected.  Specifically, in order to work
	 *   perfectly dwc2 really needs quite spectacular interrupt latency
	 *   requirements.  It needs to be able to handle its interrupts
	 *   completely within 125 us of them being asserted. That not only
	 *   means that the dwc2 interrupt handler needs to be fast but it
	 *   means that nothing else in the system has to block dwc2 for a long
	 *   time.  We can help with the dwc2 parts of this, but it's hard to
	 *   guarantee that a system will have interrupt latency < 125 us, so
	 *   we have to be robust to some misses.
	 */
	if (qh->start_active_frame == qh->next_active_frame ||
	    dwc2_frame_num_gt(prev_frame_number, qh->start_active_frame)) {
		u16 ideal_start = qh->start_active_frame;
		int periods_in_map;

		/*
		 * Adjust interval as per gcd with map size.
		 * See pmap_schedule() for more details here.
		 */
		if (qh->do_split || qh->dev_speed == USB_SPEED_HIGH)
			periods_in_map = DWC2_HS_SCHEDULE_UFRAMES;
		else
			periods_in_map = DWC2_LS_SCHEDULE_FRAMES;
		interval = gcd(interval, periods_in_map);

		do {
			qh->start_active_frame = dwc2_frame_num_inc(
				qh->start_active_frame, interval);
		} while (dwc2_frame_num_gt(prev_frame_number,
					   qh->start_active_frame));

		missed = dwc2_frame_num_dec(qh->start_active_frame,
					    ideal_start);
	}

exit:
	qh->next_active_frame = qh->start_active_frame;

	return missed;
}