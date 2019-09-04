#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ar9170 {int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  usb_tasklet; int /*<<< orphan*/  rx_anch; int /*<<< orphan*/  tx_anch; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_UNKNOWN_STATE ; 
 int /*<<< orphan*/  carl9170_set_state (struct ar9170*,int /*<<< orphan*/ ) ; 
 int carl9170_usb_flush (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_handle_tx_err (struct ar9170*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_poison_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carl9170_usb_cancel_urbs(struct ar9170 *ar)
{
	int err;

	carl9170_set_state(ar, CARL9170_UNKNOWN_STATE);

	err = carl9170_usb_flush(ar);
	if (err)
		dev_err(&ar->udev->dev, "stuck tx urbs!\n");

	usb_poison_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);
	usb_poison_anchored_urbs(&ar->rx_anch);

	tasklet_kill(&ar->usb_tasklet);

	usb_scuttle_anchored_urbs(&ar->rx_work);
	usb_scuttle_anchored_urbs(&ar->rx_pool);
	usb_scuttle_anchored_urbs(&ar->tx_cmd);
}