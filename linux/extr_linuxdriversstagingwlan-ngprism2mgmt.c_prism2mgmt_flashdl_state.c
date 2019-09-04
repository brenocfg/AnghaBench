#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlandevice {scalar_t__ msdstate; int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_4__ {int data; void* status; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct p80211msg_p2req_flashdl_state {TYPE_2__ resultcode; TYPE_1__ enable; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P80211ENUM_ifstate_fwload ; 
 void* P80211ENUM_msgitem_status_data_ok ; 
 void* P80211ENUM_resultcode_implementation_failure ; 
 int P80211ENUM_resultcode_success ; 
 scalar_t__ P80211ENUM_truth_true ; 
 scalar_t__ WLAN_MSD_FWLOAD ; 
 scalar_t__ WLAN_MSD_HWPRESENT ; 
 int /*<<< orphan*/  hfa384x_drvr_flashdl_disable (struct hfa384x*) ; 
 scalar_t__ hfa384x_drvr_flashdl_enable (struct hfa384x*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int prism2sta_ifstate (struct wlandevice*,int /*<<< orphan*/ ) ; 

int prism2mgmt_flashdl_state(struct wlandevice *wlandev, void *msgp)
{
	int result = 0;
	struct hfa384x *hw = wlandev->priv;
	struct p80211msg_p2req_flashdl_state *msg = msgp;

	if (wlandev->msdstate != WLAN_MSD_FWLOAD) {
		netdev_err(wlandev->netdev,
			   "flashdl_state(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		return 0;
	}

	/*
	 ** Note: Interrupts are locked out if this is an AP and are NOT
	 ** locked out if this is a station.
	 */

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	if (msg->enable.data == P80211ENUM_truth_true) {
		if (hfa384x_drvr_flashdl_enable(hw)) {
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		} else {
			msg->resultcode.data = P80211ENUM_resultcode_success;
		}
	} else {
		hfa384x_drvr_flashdl_disable(hw);
		msg->resultcode.data = P80211ENUM_resultcode_success;
		/* NOTE: At this point, the MAC is in the post-reset
		 * state and the driver is in the fwload state.
		 * We need to get the MAC back into the fwload
		 * state.  To do this, we set the nsdstate to HWPRESENT
		 * and then call the ifstate function to redo everything
		 * that got us into the fwload state.
		 */
		wlandev->msdstate = WLAN_MSD_HWPRESENT;
		result = prism2sta_ifstate(wlandev, P80211ENUM_ifstate_fwload);
		if (result != P80211ENUM_resultcode_success) {
			netdev_err(wlandev->netdev,
				   "prism2sta_ifstate(fwload) failed, P80211ENUM_resultcode=%d\n",
				   result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
			result = -1;
		}
	}

	return 0;
}