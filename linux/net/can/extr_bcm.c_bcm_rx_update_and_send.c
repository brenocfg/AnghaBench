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
struct canfd_frame {int flags; } ;
struct bcm_op {scalar_t__ kt_lastmsg; int /*<<< orphan*/  kt_ival2; int /*<<< orphan*/  thrtimer; int /*<<< orphan*/  cfsiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_SOFT ; 
 int RX_RECV ; 
 int RX_THR ; 
 int /*<<< orphan*/  bcm_rx_changed (struct bcm_op*,struct canfd_frame*) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_us_delta (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct canfd_frame*,struct canfd_frame const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_rx_update_and_send(struct bcm_op *op,
				   struct canfd_frame *lastdata,
				   const struct canfd_frame *rxdata)
{
	memcpy(lastdata, rxdata, op->cfsiz);

	/* mark as used and throttled by default */
	lastdata->flags |= (RX_RECV|RX_THR);

	/* throttling mode inactive ? */
	if (!op->kt_ival2) {
		/* send RX_CHANGED to the user immediately */
		bcm_rx_changed(op, lastdata);
		return;
	}

	/* with active throttling timer we are just done here */
	if (hrtimer_active(&op->thrtimer))
		return;

	/* first reception with enabled throttling mode */
	if (!op->kt_lastmsg)
		goto rx_changed_settime;

	/* got a second frame inside a potential throttle period? */
	if (ktime_us_delta(ktime_get(), op->kt_lastmsg) <
	    ktime_to_us(op->kt_ival2)) {
		/* do not send the saved data - only start throttle timer */
		hrtimer_start(&op->thrtimer,
			      ktime_add(op->kt_lastmsg, op->kt_ival2),
			      HRTIMER_MODE_ABS_SOFT);
		return;
	}

	/* the gap was that big, that throttling was not needed here */
rx_changed_settime:
	bcm_rx_changed(op, lastdata);
	op->kt_lastmsg = ktime_get();
}