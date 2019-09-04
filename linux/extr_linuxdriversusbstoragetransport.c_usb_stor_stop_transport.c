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
struct us_data {int /*<<< orphan*/  current_sg; int /*<<< orphan*/  dflags; int /*<<< orphan*/  current_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_FLIDX_SG_ACTIVE ; 
 int /*<<< orphan*/  US_FLIDX_URB_ACTIVE ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sg_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

void usb_stor_stop_transport(struct us_data *us)
{
	/*
	 * If the state machine is blocked waiting for an URB,
	 * let's wake it up.  The test_and_clear_bit() call
	 * guarantees that if a URB has just been submitted,
	 * it won't be cancelled more than once.
	 */
	if (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->dflags)) {
		usb_stor_dbg(us, "-- cancelling URB\n");
		usb_unlink_urb(us->current_urb);
	}

	/* If we are waiting for a scatter-gather operation, cancel it. */
	if (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags)) {
		usb_stor_dbg(us, "-- cancelling sg request\n");
		usb_sg_cancel(&us->current_sg);
	}
}