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
struct chaoskey {int valid; int used; int reading; int reads_started; int /*<<< orphan*/  interface; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  urb; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALEA_FIRST_TIMEOUT ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAK_TIMEOUT ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_translate_errors (int) ; 
 int /*<<< orphan*/  wait ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _chaoskey_fill(struct chaoskey *dev)
{
	DEFINE_WAIT(wait);
	int result;
	bool started;

	usb_dbg(dev->interface, "fill");

	/* Return immediately if someone called before the buffer was
	 * empty */
	if (dev->valid != dev->used) {
		usb_dbg(dev->interface, "not empty yet (valid %d used %d)",
			dev->valid, dev->used);
		return 0;
	}

	/* Bail if the device has been removed */
	if (!dev->present) {
		usb_dbg(dev->interface, "device not present");
		return -ENODEV;
	}

	/* Make sure the device is awake */
	result = usb_autopm_get_interface(dev->interface);
	if (result) {
		usb_dbg(dev->interface, "wakeup failed (result %d)", result);
		return result;
	}

	dev->reading = true;
	result = usb_submit_urb(dev->urb, GFP_KERNEL);
	if (result < 0) {
		result = usb_translate_errors(result);
		dev->reading = false;
		goto out;
	}

	/* The first read on the Alea takes a little under 2 seconds.
	 * Reads after the first read take only a few microseconds
	 * though.  Presumably the entropy-generating circuit needs
	 * time to ramp up.  So, we wait longer on the first read.
	 */
	started = dev->reads_started;
	dev->reads_started = true;
	result = wait_event_interruptible_timeout(
		dev->wait_q,
		!dev->reading,
		(started ? NAK_TIMEOUT : ALEA_FIRST_TIMEOUT) );

	if (result < 0)
		goto out;

	if (result == 0)
		result = -ETIMEDOUT;
	else
		result = dev->valid;
out:
	/* Let the device go back to sleep eventually */
	usb_autopm_put_interface(dev->interface);

	usb_dbg(dev->interface, "read %d bytes", dev->valid);

	return result;
}