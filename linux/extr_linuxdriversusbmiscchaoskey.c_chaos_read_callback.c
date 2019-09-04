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
struct urb {int status; scalar_t__ actual_length; struct chaoskey* context; } ;
struct chaoskey {int reading; int /*<<< orphan*/  wait_q; scalar_t__ used; scalar_t__ valid; int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  usb_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chaos_read_callback(struct urb *urb)
{
	struct chaoskey *dev = urb->context;
	int status = urb->status;

	usb_dbg(dev->interface, "callback status (%d)", status);

	if (status == 0)
		dev->valid = urb->actual_length;
	else
		dev->valid = 0;

	dev->used = 0;

	/* must be seen first before validity is announced */
	smp_wmb();

	dev->reading = false;
	wake_up(&dev->wait_q);
}