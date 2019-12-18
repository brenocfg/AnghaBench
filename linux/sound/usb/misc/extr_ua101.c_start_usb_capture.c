#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** urbs; } ;
struct ua101 {TYPE_3__ capture; int /*<<< orphan*/  states; scalar_t__ rate_feedback_count; scalar_t__ rate_feedback_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  complete; } ;
struct TYPE_6__ {TYPE_1__ urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_URB_COMPLETED ; 
 int /*<<< orphan*/  DISCONNECTED ; 
 int ENODEV ; 
 int /*<<< orphan*/  INTF_CAPTURE ; 
 int /*<<< orphan*/  USB_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int enable_iso_interface (struct ua101*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_capture_urb_complete ; 
 int /*<<< orphan*/  kill_stream_urbs (TYPE_3__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_usb_capture (struct ua101*) ; 
 int submit_stream_urbs (struct ua101*,TYPE_3__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_usb_capture(struct ua101 *ua)
{
	int err;

	if (test_bit(DISCONNECTED, &ua->states))
		return -ENODEV;

	if (test_bit(USB_CAPTURE_RUNNING, &ua->states))
		return 0;

	kill_stream_urbs(&ua->capture);

	err = enable_iso_interface(ua, INTF_CAPTURE);
	if (err < 0)
		return err;

	clear_bit(CAPTURE_URB_COMPLETED, &ua->states);
	ua->capture.urbs[0]->urb.complete = first_capture_urb_complete;
	ua->rate_feedback_start = 0;
	ua->rate_feedback_count = 0;

	set_bit(USB_CAPTURE_RUNNING, &ua->states);
	err = submit_stream_urbs(ua, &ua->capture);
	if (err < 0)
		stop_usb_capture(ua);
	return err;
}