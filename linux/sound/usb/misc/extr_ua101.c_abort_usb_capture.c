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
struct ua101 {int /*<<< orphan*/  rate_feedback_wait; int /*<<< orphan*/  alsa_capture_wait; int /*<<< orphan*/  states; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CAPTURE_RUNNING ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abort_usb_capture(struct ua101 *ua)
{
	if (test_and_clear_bit(USB_CAPTURE_RUNNING, &ua->states)) {
		wake_up(&ua->alsa_capture_wait);
		wake_up(&ua->rate_feedback_wait);
	}
}