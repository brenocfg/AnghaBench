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
struct urb {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  rx_anch; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_pool_urbs; } ;

/* Variables and functions */
 int AR9170_NUM_RX_URBS_POOL ; 
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int /*<<< orphan*/  CARL9170_STOPPED ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* carl9170_usb_alloc_rx_urb (struct ar9170*,int /*<<< orphan*/ ) ; 
 int carl9170_usb_submit_rx_urb (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carl9170_usb_init_rx_bulk_urbs(struct ar9170 *ar)
{
	struct urb *urb;
	int i, err = -EINVAL;

	/*
	 * The driver actively maintains a second shadow
	 * pool for inactive, but fully-prepared rx urbs.
	 *
	 * The pool should help the driver to master huge
	 * workload spikes without running the risk of
	 * undersupplying the hardware or wasting time by
	 * processing rx data (streams) inside the urb
	 * completion (hardirq context).
	 */
	for (i = 0; i < AR9170_NUM_RX_URBS_POOL; i++) {
		urb = carl9170_usb_alloc_rx_urb(ar, GFP_KERNEL);
		if (!urb) {
			err = -ENOMEM;
			goto err_out;
		}

		usb_anchor_urb(urb, &ar->rx_pool);
		atomic_inc(&ar->rx_pool_urbs);
		usb_free_urb(urb);
	}

	err = carl9170_usb_submit_rx_urb(ar, GFP_KERNEL);
	if (err)
		goto err_out;

	/* the device now waiting for the firmware. */
	carl9170_set_state_when(ar, CARL9170_STOPPED, CARL9170_IDLE);
	return 0;

err_out:

	usb_scuttle_anchored_urbs(&ar->rx_pool);
	usb_scuttle_anchored_urbs(&ar->rx_work);
	usb_kill_anchored_urbs(&ar->rx_anch);
	return err;
}