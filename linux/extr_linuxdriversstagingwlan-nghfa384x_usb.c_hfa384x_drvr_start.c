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
typedef  int u16 ;
struct hfa384x {int /*<<< orphan*/  state; TYPE_1__* wlandev; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  endp_out; int /*<<< orphan*/  usb; int /*<<< orphan*/  endp_in; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFA384x_STATE_RUNNING ; 
 int /*<<< orphan*/  USB_RECIP_ENDPOINT ; 
 int hfa384x_cmd_initialize (struct hfa384x*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int submit_rx_urb (struct hfa384x*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_get_std_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

int hfa384x_drvr_start(struct hfa384x *hw)
{
	int result, result1, result2;
	u16 status;

	might_sleep();

	/* Clear endpoint stalls - but only do this if the endpoint
	 * is showing a stall status. Some prism2 cards seem to behave
	 * badly if a clear_halt is called when the endpoint is already
	 * ok
	 */
	result =
	    usb_get_std_status(hw->usb, USB_RECIP_ENDPOINT, hw->endp_in,
			       &status);
	if (result < 0) {
		netdev_err(hw->wlandev->netdev, "Cannot get bulk in endpoint status.\n");
		goto done;
	}
	if ((status == 1) && usb_clear_halt(hw->usb, hw->endp_in))
		netdev_err(hw->wlandev->netdev, "Failed to reset bulk in endpoint.\n");

	result =
	    usb_get_std_status(hw->usb, USB_RECIP_ENDPOINT, hw->endp_out,
			       &status);
	if (result < 0) {
		netdev_err(hw->wlandev->netdev, "Cannot get bulk out endpoint status.\n");
		goto done;
	}
	if ((status == 1) && usb_clear_halt(hw->usb, hw->endp_out))
		netdev_err(hw->wlandev->netdev, "Failed to reset bulk out endpoint.\n");

	/* Synchronous unlink, in case we're trying to restart the driver */
	usb_kill_urb(&hw->rx_urb);

	/* Post the IN urb */
	result = submit_rx_urb(hw, GFP_KERNEL);
	if (result != 0) {
		netdev_err(hw->wlandev->netdev,
			   "Fatal, failed to submit RX URB, result=%d\n",
			   result);
		goto done;
	}

	/* Call initialize twice, with a 1 second sleep in between.
	 * This is a nasty work-around since many prism2 cards seem to
	 * need time to settle after an init from cold. The second
	 * call to initialize in theory is not necessary - but we call
	 * it anyway as a double insurance policy:
	 * 1) If the first init should fail, the second may well succeed
	 *    and the card can still be used
	 * 2) It helps ensures all is well with the card after the first
	 *    init and settle time.
	 */
	result1 = hfa384x_cmd_initialize(hw);
	msleep(1000);
	result = hfa384x_cmd_initialize(hw);
	result2 = result;
	if (result1 != 0) {
		if (result2 != 0) {
			netdev_err(hw->wlandev->netdev,
				   "cmd_initialize() failed on two attempts, results %d and %d\n",
				   result1, result2);
			usb_kill_urb(&hw->rx_urb);
			goto done;
		} else {
			pr_debug("First cmd_initialize() failed (result %d),\n",
				 result1);
			pr_debug("but second attempt succeeded. All should be ok\n");
		}
	} else if (result2 != 0) {
		netdev_warn(hw->wlandev->netdev, "First cmd_initialize() succeeded, but second attempt failed (result=%d)\n",
			    result2);
		netdev_warn(hw->wlandev->netdev,
			    "Most likely the card will be functional\n");
		goto done;
	}

	hw->state = HFA384x_STATE_RUNNING;

done:
	return result;
}