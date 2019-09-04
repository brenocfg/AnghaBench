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
struct ar9170 {int /*<<< orphan*/  rx_anch_urbs; int /*<<< orphan*/  rx_pool_urbs; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_anch; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_NUM_RX_URBS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int carl9170_usb_submit_rx_urb(struct ar9170 *ar, gfp_t gfp)
{
	struct urb *urb;
	int err = 0, runs = 0;

	while ((atomic_read(&ar->rx_anch_urbs) < AR9170_NUM_RX_URBS) &&
		(runs++ < AR9170_NUM_RX_URBS)) {
		err = -ENOSPC;
		urb = usb_get_from_anchor(&ar->rx_pool);
		if (urb) {
			usb_anchor_urb(urb, &ar->rx_anch);
			err = usb_submit_urb(urb, gfp);
			if (unlikely(err)) {
				usb_unanchor_urb(urb);
				usb_anchor_urb(urb, &ar->rx_pool);
			} else {
				atomic_dec(&ar->rx_pool_urbs);
				atomic_inc(&ar->rx_anch_urbs);
			}
			usb_free_urb(urb);
		}
	}

	return err;
}